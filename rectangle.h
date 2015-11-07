/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    rectangle.h
**************************************************************/

#ifndef __RECTANGLE_H
#define __RECTANGLE_H

#include <QPainter>
#include <QGraphicsRectItem>

class Rectangle : public QGraphicsRectItem
{
 public:
    Rectangle(QGraphicsItem * parent, float shape);
	QVariant itemChange (GraphicsItemChange change, const QVariant &value);

 protected:
	void paint ( QPainter * painter, 
		const QStyleOptionGraphicsItem * option, QWidget * widget );

 private:
    float shape_length;
};

#endif 
