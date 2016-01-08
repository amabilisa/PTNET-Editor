/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    tabwidget.cpp
**************************************************************/

#include "tabwidget.h"
#include <QDebug>

TabWidget::TabWidget(QWidget * parent)
    :QTabWidget (parent)
{
    nets_indexes = 0;
    setMovable (true);
    setTabsClosable(false);
    connect(this, SIGNAL(tabCloseRequested(int)),
            this, SLOT(closeTab(int)));

    createNew ();
}

/* zoom +/- the current tab */
void TabWidget::zoom (int val)
{
    qobject_cast<PTNtab*>(currentWidget ())->scaleView (val);
}

/* Undo the last Action */
void TabWidget::undo ()
{
    qobject_cast<PTNtab*>(currentWidget ())->undo ();
}

/* Redo the last undown action */
void TabWidget::redo ()
{
    qobject_cast<PTNtab*>(currentWidget ())->redo ();
}

/* remove selected items */
void TabWidget::removeItems ()
{
    qobject_cast<PTNtab*>(currentWidget ())->removeItems ();
}

/* close tab */
void TabWidget::closeTab(int index)
{
    PTNtab * tab = qobject_cast<PTNtab *>(widget(index));
    setCurrentWidget(tab);

    if(!tab->isSaved())
    {
        QMessageBox::StandardButton action;

        action = QMessageBox::warning(this,
                       "Save", "Save changes before closing ?",
                        QMessageBox::Save | QMessageBox::Discard |
                        QMessageBox::Cancel, QMessageBox::Save);

      if(action == QMessageBox::Save)
         save();
      else if(action == QMessageBox::Cancel)
          return;
    }

      removeTab(index);
      delete tab;
	tab=0;

      if (count() <= 1)
        setTabsClosable(false);
      else
        setTabsClosable(true);

}

/* add an asterisk "*" at the end of the tab's title if
 * its content was changed. Otherwise remove it. */
void TabWidget::updateTitle (bool changed)
{
    int index = currentIndex();
    QString text = tabText(index);

    if (!changed && (!text.endsWith("*")))
            setTabText(index, QString(text+"*"));
    else
    {
        text.remove(text.size()-1, 1);
        setTabText(index, text);
    } 
}

/* open */
bool TabWidget::open (MessageHandler &messageHandler)
{
    //![0] get file name
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open PNML Document"), QDir::currentPath(),
              tr("Petri Net Files (*.pnml)"));

    if(filename.isNull())
        return false;

    //![1] check if the file is already opened
    if(fileNames.contains(filename))
    {
        for(int i=0; i<count(); i++)
        {
            PTNtab * tab = qobject_cast<PTNtab*>(widget(i));
            if(tab->getFilename() == filename)
            {
                setCurrentWidget(tab);
                return true;
            }
        }
    }else
    {
        fileNames << filename;
    }

    QFile file(filename);

    //[2]! validate xml file
    if(!validateXml(file, messageHandler))
	return false;

    //[3]! parse xml file
    file.seek(0);
    QTextStream textstream(&file);
    QString xmlContent = textstream.readAll();
    file.close();

    XmlParser parser;
    if(!parser.parseXML(xmlContent))
        return false;

    //[4]! ok :)
    PTNET_ATTR net = parser.getXML_net ();
    PTNtab * tab = new PTNtab(net, filename);
    addTab(tab, QString(net.name+".pnml"));
    sig_slots_connect(tab);
    setTabToolTip(currentIndex(), filename);

    return true;
}

bool TabWidget::validateXml(QFile& file, MessageHandler &messageHandler)
{
    //![0] validate XML schema
    QXmlSchema schema;
    schema.setMessageHandler(&messageHandler);
    schema.load(QUrl::fromLocalFile(":/schemas/ptnet.xsd"));

    if(!schema.isValid())
        return false; 
    
    //![1] open file
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Loading File Error", file.errorString ());
        return false;
    }

    //![2] validate file against XML schema
    QXmlSchemaValidator validator(schema);
    validator.setMessageHandler(&messageHandler);
    if(!validator.validate(&file, QUrl::fromLocalFile(file.fileName())))
    {
        file.close();
        return false;
    }

  return true;
}

/* create New Petri Net */
void TabWidget::createNew ()
{
    QVariant v(nets_indexes);
    PTNtab * tab = new PTNtab("net"+v.toString(), 0);
    addTab(tab, QString("petrinet "+v.toString()));
    sig_slots_connect(tab);
    nets_indexes ++;
}

void TabWidget::sig_slots_connect(PTNtab * tab)
{
    connect (tab, SIGNAL(canRedoChange (bool)), 
	this, SIGNAL(canRedoChange (bool)));
    connect (tab, SIGNAL(canUndoChange (bool)), 
	this, SIGNAL(canUndoChange (bool)));
    connect (tab, SIGNAL(netChanged(bool)), 
	this, SLOT(updateTitle (bool)));
    connect (tab, SIGNAL(errorMessage (const QString&)), 
	this, SIGNAL(errorMessage (const QString&)));

    if(count() > 1)
        setTabsClosable(true);

    setCurrentWidget(tab);
}

/* save */
void TabWidget::save ()
{
    PTNtab * tab = qobject_cast<PTNtab*>(currentWidget());
    QString filename = tab->getFilename();

    if(filename.isNull())
        saveAs(); 
    else
    {
      QFile file(filename);

      if(!file.open(QIODevice::WriteOnly))
          QMessageBox::critical(this, "Open File Error", \
		"The file could not be opened.");

      XmlWriter writer(tab->toXml());
      writer.writeXML(&file);

      tab->cleanUndostack();
    }
}

/* save As */
void TabWidget::saveAs()
{
    PTNtab * tab = qobject_cast<PTNtab*>(currentWidget());
    int index = currentIndex();

    QString filename = QFileDialog::getSaveFileName(this,
                          tr("Save As PNML Document"),
                                QDir::currentPath(),
                          tr("Petri Net Files (*.pnml)"));

    if(filename.isNull())
        return;


    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly))
    { 
       QMessageBox::critical(this, "Save As Error", "The Petri Net" \
                          "could not be saved to: "+filename);
 
       return;
    }

    XmlWriter writer(tab->toXml());
    writer.writeXML(&file);

    tab->setFilename(filename);
    tab->cleanUndostack();
    
    setTabToolTip(index, filename);
    QFileInfo fileInfo(filename);
    setTabText(index, fileInfo.fileName ());

    if(!fileNames.contains(filename))
         fileNames << filename;
}

void TabWidget::exportNet ()
{
    PTNtab * tab = qobject_cast<PTNtab *>(currentWidget());

    if(tab->isNetEmpty()){
      QMessageBox::information(this, "Export", "The Petri Net is empty!",
            QMessageBox::Ok, QMessageBox::Ok);
      return;
    }

  QString filename = QFileDialog::getSaveFileName(this,
     tr("export Petri Net"), QString(QDir::currentPath()+"/exported/unnamed"),
     tr("image Files (*.png)"));

  if(filename.isNull())
    return;

  tab->exportNet (filename);
}

