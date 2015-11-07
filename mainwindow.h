/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    mainwindow.h
**************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>
#include <QStatusBar>
#include <QSlider>

#include "tabwidget.h"
#include "dockwidget.h"
#include "graphdock.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);
    ~MainWindow();
    void updateWidgets (int mode);

protected:

    void closeEvent ( QCloseEvent * event );

public slots:

    void buttonGroupClicked (int id);
    void tabChanged (int index);
    void sliderValueChanged (int value);
    void open ();
    void about();

private:

    QMenu   * fileMenu;
    QAction * newMenuAct;
    QAction * openMenuAct;
    QAction * saveMenuAct;
    QAction * exportMenuAct;
    QAction * quitMenuAct;

    QMenu   * editMenu;
    QAction * undoMenuAct;
    QAction * redoMenuAct;
    QAction * removeMenuAct;

    QMenu   * helpMenu;
    QAction * aboutMenuAct;

    TabWidget  * tabWidget;
    QStatusBar * statusBar;

    QToolBar * toolBar;
    QButtonGroup * buttonGroup;
    QToolButton  * newToolButton;
    QToolButton  * openToolButton;
    QToolButton  * saveToolButton;

    QToolButton  * undoToolButton;
    QToolButton  * redoToolButton;

    QToolButton  * removeToolButton;
    QToolButton  * cursorToolButton;

    QToolButton  * addPlaceToolButton;
    QToolButton  * addTransToolButton;
    QToolButton  * drawArcToolButton;
    QToolButton  * addTokenToolButton;
    QToolButton  * subTokenToolButton;

    QToolButton  * animateToolButton;

    GraphDock  * graphDock;
    DockWidget * buttomDock;
    QSlider    * slider;

    void createMenuBar ();
    void createToolBar ();
    void createDocks ();
    void createStatusBar ();

};

#endif // MAINWINDOW_H
