#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QToolButton>

class ToolBar : public QToolBar
{
public:
    ToolBar();
    ~ToolBar();

private:
    QToolButton * newButton;
    QToolButton * openButton;
    QToolButton * saveButton;
    QToolButton * undoButton;
    QToolButton * redoButton;
    QToolButton * deleteButton;
    QToolButton * addPlaceButton;
    QToolButton * addTransitionButton;
    QToolButton * drawArcButton;
    QToolButton * setCursorButton;
    QToolButton * addTokenButton;
    QToolButton * removeTokenButton;
    QToolButton * animateButton;
    QToolButton * exportButton;
};

#endif // TOOLBAR_H
