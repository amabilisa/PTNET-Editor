/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    arcedgeselectionrectangle.h
**************************************************************/

#ifndef __ARCSELECTIONRECTANGLE_H
#define __ARCSELECTIONRECTANGLE_H

#include <QPainter>
#include <QGraphicsRectItem>

class ArcEdgeSelectionRectangle : public QGraphicsRectItem
{
 public:
    ArcEdgeSelectionRectangle(QGraphicsItem * parent, float shape);
	QVariant itemChange (GraphicsItemChange change, const QVariant &value);

 protected:
	void paint ( QPainter * painter, 
		const QStyleOptionGraphicsItem * option, QWidget * widget );

 private:
    float shape_length;
};

#endif 
