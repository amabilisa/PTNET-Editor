/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    arc.h
**************************************************************/

#ifndef ARC_H
#define ARC_H

#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsSimpleTextItem>

#include "arcedgeselectionrectangle.h"

#include "defs.h"

class Arc : public QGraphicsPathItem
{
 public:

    enum { Type = UserType + 3 };

    Arc(QGraphicsItem * item1, QString id1,QGraphicsItem * item2,
        QString id2, QPainterPath arc_path, const QString &id, int w = 1);

    Arc(QGraphicsItem * item1, QGraphicsItem * item2,
        QPainterPath paintpath, const ARC_ATTR &arc);

    ~Arc();

    void createArc();
    ARC_ATTR toXml() const;

    void updatePosition();
    void showRects(bool show);

    QString getId();
    int getWeight() const;
    void setWeight(int w);

    QGraphicsItem * getSourceItem() const;
    QGraphicsItem * getTargetItem() const;

    int type () const;
    QPainterPath shape() const;
    QRectF boundingRect() const;

 protected:

    void paint ( QPainter * painter, 
	const QStyleOptionGraphicsItem * option, 
	QWidget * widget );

 private:

    QString id;
    QString source_id;
    QString target_id;
    int weight;

    QPolygonF ArcHead;
    QGraphicsSimpleTextItem * label;

    QList<ArcEdgeSelectionRectangle *> rects;

    QGraphicsItem * sourceItem;
    QGraphicsItem * targetItem;

    QPointF intersectionPoint1(QGraphicsItem * circle, QLineF * line) const;
    QPointF intersectionPoint2(QGraphicsItem * rectangle, QLineF * line) const;

    QColor color;
};

#endif // ARC_H
