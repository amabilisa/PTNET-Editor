/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    mainwindow.cpp
**************************************************************/

#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    tabWidget = new TabWidget;
    setCentralWidget (tabWidget);

    createMenuBar();
    createToolBar ();
    createDocks ();
    createStatusBar ();

    connect(tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(tabChanged(int)));
    connect(tabWidget, SIGNAL(errorMessage (QString)),
            buttomDock, SLOT(showMessage (QString)));
}

/* Open */
void MainWindow::open ()
{
    statusBar->showMessage("Open an existing PNML document ...");
    if(tabWidget->open(buttomDock->getMessageHandler()))
        statusBar->showMessage("Document loaded and opened.", 1000);
    else
        statusBar->showMessage("Document was not opened.", 1000); 
}

/* button group clicked */
void MainWindow::buttonGroupClicked(int id)
{
    PTNtab* tab = qobject_cast<PTNtab*>(tabWidget->currentWidget ());
    if (id == animationMode)
    {
        buttomDock->show();
        if(!tab->checkNet())
        {
            tab->setMode (normalMode);
                return;
        }else
         {
            // Generate Reachability/ Coverability graph
            tab->setMode (animationMode);
            GraphVisualizer * graphvis = tab->createGraphVis();
            graphDock->setGraph(graphvis);

         }
    }

    tab->setMode (id);
    updateWidgets (id);
}

/* tab changed */
void MainWindow::tabChanged(int index)
{
    PTNtab * tab = qobject_cast<PTNtab*>(tabWidget->widget(index));
    int mode = tab->getMode();
    graphDock->setGraph(tab->getGraphVis());
    updateWidgets (mode);

    QAbstractButton * button = buttonGroup->button (mode);
    button->setChecked(true);

    slider->setValue(tab->scaleValue());
}

/* update widget when the tab changed */
void MainWindow::updateWidgets (int mode)
{
    bool disable;

    if(mode == animationMode)
        disable = true;
    else
        disable = false;

    saveMenuAct->setDisabled (disable);
    saveToolButton->setDisabled (disable);
    addPlaceToolButton->setDisabled (disable);
    addTransToolButton->setDisabled (disable);
    drawArcToolButton->setDisabled (disable);
    addTokenToolButton->setDisabled (disable);
    subTokenToolButton->setDisabled (disable);

    PTNtab * tab = qobject_cast<PTNtab*>(tabWidget->currentWidget());

    if (mode != animationMode)
    {
        redoToolButton->setEnabled(tab->canRedo());
        undoToolButton->setEnabled(tab->canUndo());
        redoMenuAct->setEnabled (tab->canRedo());
        undoMenuAct->setEnabled (tab->canUndo());
    }else
    {
        redoToolButton->setEnabled(false);
        undoToolButton->setEnabled(false);
        redoMenuAct->setEnabled (false);
        undoMenuAct->setEnabled (false);
    }
}

/* create menus bar */
void MainWindow::createMenuBar()
{
    // File Menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    newMenuAct = fileMenu->addAction(tr("&New Net"));
    newMenuAct->setIcon(QIcon::fromTheme("window-new"));
    newMenuAct->setShortcut(QKeySequence("Ctrl+N"));
        connect(newMenuAct, SIGNAL(triggered()), tabWidget, SLOT(createNew()));
    openMenuAct = fileMenu->addAction(tr("&Open Net"));
    openMenuAct->setIcon(QIcon::fromTheme("folder-open"));
    openMenuAct->setShortcut(QKeySequence("Ctrl+O"));
        connect(openMenuAct, SIGNAL(triggered()), this, SLOT(open()));
            fileMenu->addSeparator();
    saveMenuAct = fileMenu->addAction(tr("&Save"));
    saveMenuAct->setIcon(QIcon::fromTheme("document-save"));
    saveMenuAct->setShortcut(QKeySequence("Ctrl+S"));
        connect(saveMenuAct, SIGNAL(triggered()), tabWidget, SLOT(save()));
    exportMenuAct = fileMenu->addAction(tr("&Export"));
    //exportMenuAct->setIcon(QIcon(QPixmap("")));
    exportMenuAct->setShortcut(QKeySequence("Ctrl+E"));
        connect(exportMenuAct, SIGNAL(triggered()), tabWidget, SLOT(exportNet()));
            fileMenu->addSeparator();
    quitMenuAct = fileMenu->addAction(tr("&Exit"));
    quitMenuAct->setIcon(QIcon::fromTheme("application-exit"));
    quitMenuAct->setShortcut(QKeySequence("Ctrl+Q"));
        connect(quitMenuAct, SIGNAL(triggered()), this, SLOT(close()));

    // Petri Net Menu
    editMenu = menuBar()->addMenu(tr("&Edit"));
    undoMenuAct = editMenu->addAction(tr("&Undo"));
    undoMenuAct->setIcon(QIcon::fromTheme("edit-undo"));
    undoMenuAct->setShortcut(QKeySequence("Ctrl+Z"));
    undoMenuAct->setEnabled(false);
        connect(undoMenuAct, SIGNAL(triggered()), tabWidget, SLOT(undo()));
        connect(tabWidget, SIGNAL(canUndoChange (bool)), undoMenuAct, SLOT(setEnabled (bool)));
    redoMenuAct = editMenu->addAction(tr("&Redo"));
    redoMenuAct->setIcon(QIcon::fromTheme("edit-redo"));
    redoMenuAct->setShortcut(QKeySequence("Ctrl+Shift+Z"));
    redoMenuAct->setEnabled(false);
        connect(redoMenuAct, SIGNAL(triggered()), tabWidget, SLOT(redo()));
        connect(tabWidget, SIGNAL(canRedoChange (bool)), redoMenuAct, SLOT(setEnabled (bool)));
            editMenu->addSeparator();
    removeMenuAct = editMenu->addAction(tr("&Delete"));
    removeMenuAct->setIcon(QIcon::fromTheme("edit-delete"));
    removeMenuAct->setShortcut(QKeySequence("Del"));
        connect(removeMenuAct, SIGNAL(triggered ()), tabWidget, SLOT(removeItems ()));

    // help menu
    helpMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenuAct = helpMenu->addAction(tr("&About"));
    aboutMenuAct->setIcon(QIcon::fromTheme("help-about"));
    aboutMenuAct->setShortcut(QKeySequence("Ctrl+B"));
        connect(aboutMenuAct, SIGNAL(triggered()), this, SLOT(about()));
}

/* create tool bar */
void MainWindow::createToolBar ()
{
    newToolButton = new QToolButton;
    newToolButton->setIconSize(QSize(50, 50));
    newToolButton->setIcon(QIcon::fromTheme("window-new"));
    newToolButton->setToolTip(tr("Create a new Petri Net <span style=\"color:gray;\">Ctrl+N</span>"));
    connect(newToolButton, SIGNAL(clicked()), tabWidget, SLOT(createNew()));
        openToolButton = new QToolButton;
    openToolButton->setIconSize(QSize(50, 50));
    openToolButton->setIcon(QIcon::fromTheme("folder-open"));
    openToolButton->setToolTip(tr("Open a Petri Net document <span style=\"color:gray;\">Ctrl+O</span>"));
    connect(openToolButton, SIGNAL(clicked()), this, SLOT(open()));
        saveToolButton = new QToolButton;
    saveToolButton->setIconSize(QSize(50, 50));
    saveToolButton->setIcon(QIcon::fromTheme("document-save"));
    saveToolButton->setToolTip(tr("Save the current Petri Net <span style=\"color:gray;\">Ctrl+S</span>"));
    connect(saveToolButton, SIGNAL(clicked()), tabWidget, SLOT(save()));
        undoToolButton = new QToolButton;
    undoToolButton->setIconSize(QSize(50, 50));
    undoToolButton->setIcon(QIcon::fromTheme("edit-undo"));
    undoToolButton->setToolTip(tr("Undo the last action <span style=\"color:gray;\">Ctrl+Z</span>"));
    undoToolButton->setEnabled(false);
    connect(undoToolButton, SIGNAL(clicked()), tabWidget, SLOT(undo ()));
    connect(tabWidget, SIGNAL(canUndoChange (bool)), undoToolButton, SLOT(setEnabled (bool)));
        redoToolButton = new QToolButton;
    redoToolButton->setIconSize(QSize(50, 50));
    redoToolButton->setIcon(QIcon::fromTheme("edit-redo"));
    redoToolButton->setToolTip(tr("Redo the last undone action <span style=\"color:gray;\">Ctrl+Shif+Z</span>"));
    redoToolButton->setEnabled(false);
    connect(redoToolButton, SIGNAL(clicked()), tabWidget, SLOT(redo ()));
    connect(tabWidget, SIGNAL(canRedoChange(bool)), redoToolButton, SLOT(setEnabled (bool)));
        removeToolButton = new QToolButton;
    removeToolButton->setIconSize(QSize(50, 50));
    removeToolButton->setIcon(QIcon::fromTheme("edit-delete"));
    removeToolButton->setToolTip(tr("Remove the selected items <span style=\"color:gray;\">Del</span> "));
    connect(removeToolButton, SIGNAL(clicked()), tabWidget, SLOT(removeItems ()));
        cursorToolButton = new QToolButton;
    cursorToolButton->setIconSize(QSize(50, 50));
    cursorToolButton->setCheckable(true);
    cursorToolButton->setIcon(QIcon(QPixmap(":/images/cursor.png")));
    cursorToolButton->setToolTip(tr("Normal cursor"));
        addPlaceToolButton = new QToolButton;
    addPlaceToolButton->setIconSize(QSize(50, 50));
    addPlaceToolButton->setCheckable(true);
    addPlaceToolButton->setIcon(QIcon(QPixmap(":/images/place.png")));
    addPlaceToolButton->setToolTip(tr("Add places"));
        addTransToolButton = new QToolButton;
    addTransToolButton->setIconSize(QSize(50, 50));
    addTransToolButton->setCheckable(true);
    addTransToolButton->setIcon(QIcon(QPixmap(":/images/transition.png")));
    addTransToolButton->setToolTip(tr("Add transitions"));
        drawArcToolButton = new QToolButton;
    drawArcToolButton->setIconSize(QSize(50, 50));
    drawArcToolButton->setCheckable(true);
    drawArcToolButton->setIcon(QIcon(QPixmap(":/images/arc.png")));
    drawArcToolButton->setToolTip(tr("Draw Polylines Arcs"));
        addTokenToolButton = new QToolButton;
    addTokenToolButton->setIconSize(QSize(50, 50));
    addTokenToolButton->setCheckable(true);
    addTokenToolButton->setIcon(QIcon(QPixmap(":/images/token+.png")));
    addTokenToolButton->setToolTip(tr("Add Tokens"));
        subTokenToolButton = new QToolButton;
    subTokenToolButton->setIconSize(QSize(50, 50));
    subTokenToolButton->setCheckable(true);
    subTokenToolButton->setIcon(QIcon(QPixmap(":/images/token-.png")));
    subTokenToolButton->setToolTip(tr("Delete Tokens"));
        animateToolButton = new QToolButton;
    animateToolButton->setIconSize(QSize(50, 50));
    animateToolButton->setCheckable(true);
    animateToolButton->setIcon(QIcon(QPixmap(":/images/animate.png")));
    animateToolButton->setToolTip(tr("Animate the current drawen net"));

    buttonGroup = new QButtonGroup (this);
    buttonGroup->setExclusive(true);
    buttonGroup->addButton(cursorToolButton,      normalMode);
    buttonGroup->addButton(addPlaceToolButton,    addPlaceMode);
    buttonGroup->addButton(addTransToolButton,    addTransMode);
    buttonGroup->addButton(drawArcToolButton,     drawArcMode);
    buttonGroup->addButton(animateToolButton,     animationMode);
    buttonGroup->addButton(addTokenToolButton,    addToken);
    buttonGroup->addButton(subTokenToolButton,    subToken);
        connect(buttonGroup, SIGNAL(buttonClicked (int)),
                this, SLOT(buttonGroupClicked(int)));

    // default mode = normal mode
    cursorToolButton->setChecked (true);

    toolBar = new QToolBar;
    toolBar->addWidget(newToolButton);
    toolBar->addWidget(openToolButton);
    toolBar->addWidget(saveToolButton);
        toolBar->addSeparator ();
    toolBar->addWidget(undoToolButton);
    toolBar->addWidget(redoToolButton);
        toolBar->addSeparator ();
    toolBar->addWidget(removeToolButton);
    toolBar->addWidget(cursorToolButton);
        toolBar->addSeparator ();
    toolBar->addWidget(addPlaceToolButton);
    toolBar->addWidget(addTransToolButton);
    toolBar->addWidget(drawArcToolButton);
        toolBar->addSeparator ();
    toolBar->addWidget(addTokenToolButton);
    toolBar->addWidget(subTokenToolButton);
        toolBar->addSeparator ();
    toolBar->addWidget(animateToolButton);

    toolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea | Qt::RightToolBarArea);
    addToolBar(Qt::LeftToolBarArea, toolBar);
}

/* create dock widget */
void MainWindow::createDocks ()
{
    buttomDock = new DockWidget(this);
    addDockWidget(Qt::BottomDockWidgetArea, buttomDock);
    buttomDock->setAllowedAreas(Qt::BottomDockWidgetArea);
    buttomDock->show ();

    graphDock = new GraphDock(this);
    addDockWidget(Qt::RightDockWidgetArea, graphDock);
    graphDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    graphDock->show ();
}

/* create status bar */
void MainWindow::createStatusBar ()
{
    statusBar = new QStatusBar;
    slider = new QSlider(Qt::Horizontal);
    slider->setMaximum(150);
    slider->setFixedWidth(150);
    slider->setRange(50, 150);
    slider->setSliderPosition(100);
    statusBar->addPermanentWidget(slider);
    setStatusBar(statusBar);

    connect(slider, SIGNAL(valueChanged(int)), 
	tabWidget, SLOT(zoom(int)));
    connect(slider, SIGNAL(valueChanged(int)), 
	this, SLOT(sliderValueChanged(int)));
}

void MainWindow::sliderValueChanged(int value)
{
    QVariant v(value - 50);
    slider->setToolTip(v.toString()+" %");
    QToolTip::showText ( slider->mapToGlobal(QPoint(value-20, 0)), QString(v.toString()+" %"), slider);
}

/* quit the application */
void MainWindow::closeEvent ( QCloseEvent * event )
{
    Q_UNUSED(event);

    statusBar->showMessage("Save Changes before leaving the program !");

    int i = 0;
    bool quit = true;

    while( i < tabWidget->count() && quit )
    {
        PTNtab * tab = qobject_cast<PTNtab *>(tabWidget->widget(i++));
        tabWidget->setCurrentWidget(tab);

        if(!tab->isSaved())
        {
            QMessageBox::StandardButton action = QMessageBox::warning(this,
                                "Save", "Save changes before leaving ?",
                                    QMessageBox::Save | QMessageBox::Discard |
                                        QMessageBox::Cancel, QMessageBox::Save);

            if(action == QMessageBox::Save)
            {
                tabWidget->save();
                quit = true;
            }
            else if(action == QMessageBox::Cancel)
                quit = false;
            else if(action == QMessageBox::Discard)
                quit = true;
        }
   }

        if(!quit)
        {
            statusBar->clearMessage ();
            event->ignore();
        }
}

void MainWindow::about()
{
    QString Msg(tr("<h3>PTNET Editor</h3>"\
                "<h5>Based on Qt 4.8.6 </h5>"\
                "<p><strong>PTNET Editor</strong> is a Qt desktop application." \
                " It users to draw, edit, animate, analyse by constructing the coverability graph,"\
                " convert to image format and open/save as a PNML document an ordinary <strong>Place/Transition Net</strong>.<p>" \
                "As it was mentioned above, the application use the standard "\
                "<a href=\"www.pnml.org\">PNML</a> exanchge format."\
                "<p><strong>Author:</strong> <a href=\"mailto:iabdallah@yandex.com\">Issam abdallah</a>.</p>"\
                "Tunisia, 2013-2016</p>"));

    QMessageBox::about(this, "About PTNET Editor", Msg);
}

MainWindow::~MainWindow()
{
    delete newToolButton;
    delete openToolButton;
    delete saveToolButton;
    delete undoToolButton;
    delete redoToolButton;
    delete removeToolButton;
    delete cursorToolButton;
    delete addPlaceToolButton;
    delete addTransToolButton;
    delete drawArcToolButton;
    delete addTokenToolButton;
    delete subTokenToolButton;
    delete animateToolButton;
    delete toolBar;
    delete tabWidget;
    delete graphDock;
    delete buttomDock;
    delete slider;
    delete statusBar;
}
