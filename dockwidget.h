/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    dockwidget.h
**************************************************************/

#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>
#include <QTextEdit>

#include "messagehandler.h"

class DockWidget : public QDockWidget
{
    Q_OBJECT

public:

    explicit DockWidget(QWidget * parent = 0);
	~DockWidget();

    MessageHandler& getMessageHandler ();

public slots:

	void displayMessage();
    void showMessage (const QString &msg);

private:

	QTextEdit  * textDisplay;
    MessageHandler messageHandler;
};
 
#endif
 
