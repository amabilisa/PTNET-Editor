/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    commands.h
**************************************************************/

#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>
#include "ptnscene.h"

//![0] Add place item to the scene
class AddPlaceCommand : public QUndoCommand
{
public:
    AddPlaceCommand(const QPointF &itemPos, const QString &id, PTNscene * scene);
    ~AddPlaceCommand();

    void undo ();
    void redo ();

private:
    Place * place;
    QPointF position;
    PTNscene * graphicsscene;
};
//![0]

//![1] Add transition item to the scene
class AddTransitionCommand : public QUndoCommand
{
public:
    AddTransitionCommand(const QPointF &itemPos, const QString &id, PTNscene * scene);
    ~AddTransitionCommand();

    void undo ();
    void redo ();

private:
    Transition * transition;
    QPointF position;
    PTNscene * graphicsscene;
};
//![1]

//![2] remove place/transition
class RemoveNodeCommand : public QUndoCommand
{
public:
    RemoveNodeCommand(QGraphicsItem * item, PTNscene * scene);
    ~RemoveNodeCommand();

    void undo ();
    void redo ();

private:
    QGraphicsItem * item;
    QPointF position;
    PTNscene * graphicsscene;
};
//![2]

//![3] Add arc item to the scene
class AddArcCommand : public QUndoCommand
{
public:
    AddArcCommand(QGraphicsItem * item1, QGraphicsItem * item2, const QPainterPath &arc_path,
                  const QString &id, PTNscene * scene, int w);
    ~AddArcCommand();
    void addConnections ();
    void removeConnections ();

    void undo ();
    void redo ();

private:
    Arc * arc;
    PTNscene * graphicsscene;
    QGraphicsItem * sourceItem;
    QGraphicsItem * targetItem;
    QString aid;
};
//![3]

//![4] remove arc item
class RemoveArcCommand : public QUndoCommand
{
public:
    RemoveArcCommand(QGraphicsItem * item, PTNscene * scene);
    ~RemoveArcCommand();
    void removeConnections ();
    void addConnections ();

    void undo ();
    void redo ();

private:
    Arc * arc;
    PTNscene * graphicsscene;
    QGraphicsItem * sourceItem;
    QGraphicsItem * targetItem;
    QString aid;
};
//![4]

//![5] move command
class MoveCommand : public QUndoCommand
{
public:
    MoveCommand(QGraphicsItem * movedItem, const QPointF &oldPosition);

    void undo ();
    void redo ();

private:
    QGraphicsItem * item;
    QPointF oldPos;
    QPointF newPos;
};
//![5]

#endif // COMMANDS_H
