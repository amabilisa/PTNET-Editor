/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    main.cpp
**************************************************************/

//#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    MainWindow w(0, Qt::Window);
    w.setWindowTitle("PTNET Editor");
    w.showMaximized();
    w.show();

    return a.exec();
}
