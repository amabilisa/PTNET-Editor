#include "toolbar.h"

ToolBar::ToolBar()
{

    newButton = new QToolButton;
    newButton->setCheckable(false);
    newButton->setDisabled(false);
    newButton->setIconSize(QSize(50, 50));
    newButton->setIcon(QIcon(QPixmap(":/images/new.png")));
    newButton->setToolTip(tr("Create a new Petri Net"));
    addWidget(newButton);

    openButton = new QToolButton;
    openButton->setCheckable(false);
    openButton->setDisabled(false);
    openButton->setIconSize(QSize(50, 50));
    openButton->setIcon(QIcon(QPixmap(":/images/open.png")));
    openButton->setToolTip(tr("Open a Petri Net document"));
    addWidget(openButton);

    saveButton = new QToolButton;
    saveButton->setCheckable(false);
    saveButton->setDisabled(false);
    saveButton->setIconSize(QSize(50, 50));
    saveButton->setIcon(QIcon(QPixmap(":/images/save.png")));
    saveButton->setToolTip(tr("Save the current Petri Net"));
    addWidget(saveButton);

    addSeparator ();

    undoButton = new QToolButton;
    undoButton->setCheckable(false);
    undoButton->setDisabled(false);
    undoButton->setIconSize(QSize(50, 50));
    undoButton->setIcon(QIcon(QPixmap(":/images/undo.png")));
    undoButton->setToolTip(tr("Undo the last action"));
    addWidget(undoButton);

    redoButton = new QToolButton;
    redoButton->setCheckable(false);
    redoButton->setDisabled(false);
    redoButton->setIconSize(QSize(50, 50));
    redoButton->setIcon(QIcon(QPixmap(":/images/redo.png")));
    redoButton->setToolTip(tr("Rndo the last undone action"));
    addWidget(redoButton);

    addSeparator ();

    deleteButton = new QToolButton;
    deleteButton->setCheckable(false);
    deleteButton->setDisabled(false);
    deleteButton->setIconSize(QSize(50, 50));
    deleteButton->setIcon(QIcon(QPixmap(":/images/delete.png")));
    deleteButton->setToolTip(tr("Delete selected items"));
    addWidget(deleteButton);


    setCursorButton = new QToolButton;
    setCursorButton->setCheckable(true);
    setCursorButton->setDisabled(false);
    setCursorButton->setIconSize(QSize(50, 50));
    setCursorButton->setIcon(QIcon(QPixmap(":/images/cursor.png")));
    setCursorButton->setToolTip(tr("Set the cursor"));
    addWidget(setCursorButton);

    addSeparator ();

    addPlaceButton = new QToolButton;
    addPlaceButton->setCheckable(true);
    addPlaceButton->setDisabled(false);
    addPlaceButton->setIconSize(QSize(50, 50));
    addPlaceButton->setIcon(QIcon(QPixmap(":/images/place.png")));
    addPlaceButton->setToolTip(tr("Add place"));
    addWidget(addPlaceButton);

    addTransitionButton = new QToolButton;
    addTransitionButton->setCheckable(true);
    addTransitionButton->setDisabled(false);
    addTransitionButton->setIconSize(QSize(50, 50));
    addTransitionButton->setIcon(QIcon(QPixmap(":/images/transition.png")));
    addTransitionButton->setToolTip(tr("Add transition"));
    addWidget(addTransitionButton);

    drawArcButton = new QToolButton;
    drawArcButton->setCheckable(true);
    drawArcButton->setDisabled(false);
    drawArcButton->setIconSize(QSize(50, 50));
    drawArcButton->setIcon(QIcon(QPixmap(":/images/arc.png")));
    drawArcButton->setToolTip(tr("Draw arc"));
    addWidget(drawArcButton);

    addTokenButton = new QToolButton;
    addTokenButton->setCheckable(true);
    addTokenButton->setDisabled(false);
    addTokenButton->setIconSize(QSize(50, 50));
    addTokenButton->setIcon(QIcon(QPixmap(":/images/token+.png")));
    addTokenButton->setToolTip(tr("Add a token"));
    addWidget(addTokenButton);

    removeTokenButton = new QToolButton;
    removeTokenButton->setCheckable(true);
    removeTokenButton->setDisabled(false);
    removeTokenButton->setIconSize(QSize(50, 50));
    removeTokenButton->setIcon(QIcon(QPixmap(":/images/token-.png")));
    removeTokenButton->setToolTip(tr("Remove a token"));
    addWidget(removeTokenButton);

    addSeparator ();

    animateButton = new QToolButton;
    animateButton->setCheckable(true);
    animateButton->setDisabled(false);
    animateButton->setIconSize(QSize(50, 50));
    animateButton->setIcon(QIcon(QPixmap(":/images/animate.png")));
    animateButton->setToolTip(tr("Start the animation of the current Petri Net"));
    addWidget(animateButton);

    exportButton = new QToolButton;
    exportButton->setCheckable(false);
    exportButton->setDisabled(false);
    exportButton->setIconSize(QSize(50, 50));
    exportButton->setIcon(QIcon(QPixmap(":/images/export.png")));
    exportButton->setToolTip(tr("Export the current Petri Net"));
    addWidget(exportButton);

}

ToolBar::~ToolBar()
{
    delete newButton;
    delete openButton;
    delete saveButton;
    delete undoButton;
    delete redoButton;
    delete deleteButton;
    delete addPlaceButton;
    delete addTransitionButton;
    delete drawArcButton;
    delete setCursorButton;
    delete addTokenButton;
    delete removeTokenButton;
    delete animateButton;
    delete exportButton;
}
