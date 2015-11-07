/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    tabwidget.h
**************************************************************/

#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QUrl>
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QTextStream>

#include "ptntab.h"
#include "messagehandler.h"
#include "xmlparser.h"
#include "xmlwriter.h"

class TabWidget : public QTabWidget
{
    Q_OBJECT

public:

    explicit TabWidget (QWidget * parent = 0);
    bool validateXml(QFile& file, MessageHandler &messageHandler);

signals:

    void canRedoChange (bool canRedo);
    void canUndoChange (bool canUndo);
    void tabChanged (int index);
    void errorMessage (const QString &msg);

public slots:

    void closeTab (int index);
    void removeItems ();
    void undo ();
    void redo ();
    void zoom (int val);
    void updateTitle (bool changed);
    void createNew ();
    bool open (MessageHandler &messageHandler);
    void save ();
    void saveAs ();
    void exportNet ();

protected:

    void sig_slots_connect(PTNtab * tab);

private:

    int nets_indexes;
    QStringList fileNames;
};

#endif // TABWIDGET_H
