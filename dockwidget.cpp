/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    dockwidget.cpp
**************************************************************/

#include "dockwidget.h"

DockWidget::DockWidget(QWidget * parent)
	:QDockWidget(parent) 
{
    textDisplay  = new QTextEdit;
    textDisplay->setReadOnly(true);

    setWidget(textDisplay);
    setAllowedAreas(Qt::BottomDockWidgetArea);
    setWindowTitle("Messages and Log");
    connect(&messageHandler, SIGNAL(messageDelivred()),
		this, SLOT(displayMessage()));
}

void DockWidget::displayMessage()
{
    QVariant v;
    v.setValue(messageHandler.uri());
    QString uri = v.toString();
    v.setValue(messageHandler.line());
    QString line = v.toString();
    v.setValue(messageHandler.column());
    QString column = v.toString() ;
    QString statusMessage = messageHandler.statusMessage();

    QString message(">> <span style=\"color:red;\">Error</span> in :\
                    <span style=\"color:blue;\">"+uri+"</span>, \
                    at line <span style=\"color:green;\">"+line+"</span>, \
                    column <span style=\"color:green;\">"+column+"</span> : ");

    textDisplay->insertHtml(message);
    textDisplay->insertHtml(statusMessage);
    textDisplay->insertHtml("<br>");
}

void DockWidget::showMessage (const QString &msg)
{
    textDisplay->insertHtml(msg);
    textDisplay->insertHtml("<br>");
}

MessageHandler& DockWidget::getMessageHandler ()
{
    return messageHandler;
}

DockWidget::~DockWidget()
{
  delete textDisplay;
}

