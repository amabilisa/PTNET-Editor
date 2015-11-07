#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include <QUndoStack>
#include "commands.h"

class UndoStack:public QUndoStack
{
  Q_OBJECT
 public:
	explicit UndoStack(QObject * parent = 0 );
	~UndoStack();

public slots:
	void arcInserted(QGraphicsItem * item1, QGraphicsItem * item2,
                        const QPainterPath &arc_path,
                    const QString &id, PTNscene * scene, int w);
	void itemMoved (QGraphicsItem * movedItem, const QPointF &oldPosition);
    	void nodeRemoved (QGraphicsItem * item, PTNscene * scene);
    	void arcRemoved (QGraphicsItem * item, PTNscene * scene);

};

#endif
