/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    main.cpp
**************************************************************/

#ifndef OUTLINEWIDTH
#define OUTLINEWIDTH 20
#endif

#include "arc.h"

#include <qmath.h>
#include <QDebug>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;
static double ArcSize = 10.0;
static double ArcAngle = 1.18;//Pi/3;

Arc::Arc(QGraphicsItem * item1, QString id1,QGraphicsItem * item2,
             QString id2, QPainterPath arc_path, const QString &id, int w)
{
    sourceItem = item1;
    targetItem = item2;
    setPath(arc_path);
    source_id = id1;
    target_id = id2;
    this->id = id;

    weight = w;

    createArc();
}

Arc::Arc(QGraphicsItem * item1, QGraphicsItem * item2,
     QPainterPath paintpath, const ARC_ATTR &arc)
    : QGraphicsPathItem()
{
    sourceItem = item1;
    targetItem = item2;
    setPath(paintpath);
    source_id = arc.source;
    target_id = arc.target;
    weight = arc.weight;
    id = arc.id;

    createArc();
    updatePosition();
}

void Arc::createArc()
{
    setZValue(-1000.0);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setSelected(true);

    for(int i = 1; i < path().elementCount()-1; i++ )
     {
        Rectangle * rec = new Rectangle(this,7);
        rec->setPos(path().elementAt(i).x - 7/2, path().elementAt(i).y - 7/2);
        rects << rec;
     }

    label = new QGraphicsSimpleTextItem(this);
}

/* to XML */
ARC_ATTR Arc::toXml() const
{
    ARC_ATTR arc;
    arc.id = id;
    arc.source = source_id;
    arc.target = target_id;
    arc.weight = weight;

    for(int i = 1; i < path().elementCount()-1; i++ )
        arc.points << path().elementAt(i);

    return arc;
}

Arc::~Arc()
{
    delete label;

    foreach(Rectangle * rect, rects)
        delete rect;
}

/* get Id */
QString Arc::getId()
{
    return id;
}

/* get weight */
int Arc::getWeight() const
{
    return weight;
}

void Arc::setWeight(int w)
{
  weight = w;
}

/* source item */
QGraphicsItem * Arc::getSourceItem() const
{
    return sourceItem;
}

/* target item */
QGraphicsItem * Arc::getTargetItem() const
{
    return targetItem;
}

/* show rects */
void Arc::showRects(bool show)
{
    foreach(Rectangle * rec, rects)
        rec->setVisible(show);
}

/* update position */
void Arc::updatePosition()
{
    QPointF p1 = mapFromItem(sourceItem, sourceItem->boundingRect().center());
    QPointF p2 = mapFromItem(targetItem,   targetItem->boundingRect().center());

    QPainterPath pth = path();
    pth.setElementPositionAt (0, p1.x(), p1.y());
    pth.setElementPositionAt (pth.elementCount()-1, p2.x(), p2.y());
    setPath(pth);
}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* @@@@@@ reimplemented functions @@@@@@ */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

int Arc::type () const
{
    return Type;
}

QPainterPath Arc::shape() const
{
    QPainterPath currentPath = path();
    currentPath.addPolygon(ArcHead);
    QPainterPathStroker painterPathStroker;
    painterPathStroker.setWidth(OUTLINEWIDTH);
    QPainterPath arcOutline = painterPathStroker.createStroke(currentPath);
    return arcOutline;
}

QRectF Arc::boundingRect() const
{
    qreal a = (pen().width())/2 + ArcSize/2;
    return QRectF( path().controlPointRect() )
           .normalized()
           .adjusted(-a, -a, a, a);
}

void Arc::paint ( QPainter * painter, 
	const QStyleOptionGraphicsItem * option, 
		QWidget * widget )
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(sourceItem->collidesWithItem(targetItem, Qt::IntersectsItemShape))
        return;

    QPainterPath paintpath = path();
    int elements = paintpath.elementCount();
    QPointF head_point;

    QLineF lastLine(paintpath.elementAt(elements-2).x, paintpath.elementAt(elements-2).y,
        paintpath.elementAt(elements-1).x, paintpath.elementAt(elements-1).y);

    if((targetItem->type() == QGraphicsItem::UserType+1) ||
	 (targetItem->type() == QGraphicsItem::UserType+4))
       head_point = intersectionPoint1(targetItem, &lastLine);
    else
       head_point = intersectionPoint2(targetItem, &lastLine);

    int i = 1;
    foreach(Rectangle * rec, rects)
    {
       QPointF p = mapFromItem(rec, rec->boundingRect().center());
       paintpath.setElementPositionAt(i, p.x(), p.y());
       i++;
    }

    //construct the Arc head
    double angle = qAcos(lastLine.dx() / lastLine.length());

    if (lastLine.dy() >= 0)
           angle = TwoPi - angle;

    QPointF p1 = head_point +
       QPointF(qSin(angle - ArcAngle) * ArcSize,
           qCos(angle - ArcAngle) * ArcSize);
    QPointF p3 = head_point +
       QPointF(qSin(angle - Pi + ArcAngle) * ArcSize,
           qCos(angle - Pi + ArcAngle) * ArcSize);

    QLineF l(head_point.x(), head_point.y(),
           lastLine.x1(), lastLine.y1());
    QPointF p2 = l.pointAt(5/l.length());
    ArcHead.clear();
    ArcHead << head_point << p1 << p2 << p3;

    if(isSelected())
    {
      showRects(true);
      color = QColor(0, 0, 150);
    }
    else
    {
      showRects(false);
      color = Qt::black;
    }

    // drawing Arc line
    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(paintpath);

    // drawing Arc head
    painter->setBrush(color);
    painter->drawPolygon(ArcHead);

    // drawing label
    QVariant v(weight);
    label->setText( QString("%1").arg(v.toString()) );
    label->setPos(paintpath.pointAtPercent(0.5) + QPointF(-10,0));
    label->setBrush(color);

     if(weight == 1)
       label->hide();
     else
       label->show();

    setPath(paintpath);
}

/* intersection Arc-circle */
QPointF Arc::intersectionPoint1(QGraphicsItem * circle, QLineF * line) const
{
    qreal R = 16;
    qreal x0 = (circle->mapToScene(circle->shape().controlPointRect().center())).x();
    qreal y0 = (circle->mapToScene(circle->shape().controlPointRect().center())).y();

 if(line->x2() != line->x1()) // not vrtical
  {
    QPointF yaxis_intersection;
    line->intersect( QLineF(QPointF(0, 10000), QPointF(0, -10000)), &yaxis_intersection);

    qreal a = (line->y2() - line->y1())/(line->x2() - line->x1());
    qreal b = yaxis_intersection.y();

    qreal A = 1 + a*a;
    qreal B = 2*(a*b - a*y0 - x0);
    qreal C = x0 * x0 + y0*y0 + b*b - 2*b*y0 - R*R;

    // Q > 0
    qreal Q = B*B - 4*A*C;
       qreal s1 = (-1)*(B + sqrt(Q))/(2*A);
       qreal s2 = (sqrt(Q) - B)/(2*A);
       QPointF ps1(s1, a*s1 + b);
       QPointF ps2(s2, a*s2 + b);

    if(QLineF(line->p1(), ps1).length()
        <= QLineF(line->p1(), ps2).length())
     return ps1;
    else
     return ps2;
   }
  else
   {
     // y*y - 2*y0*y + (x - x0)*(x - x0) + y0*y0 - R*R = 0
     qreal x = line->x1();
     qreal C = (x - x0)*(x - x0) + y0*y0 - R*R;
     qreal Q = 4*y0*y0 - 4*C;
       qreal s1 = y0 - sqrt(Q)/2;
       qreal s2 = y0 + sqrt(Q)/2 ;
       QPointF ps1(x, s1);
       QPointF ps2(x, s2);

    if(QLineF(line->p1(), ps1).length()
        <= QLineF(line->p1(), ps2).length())
     return ps1;
    else
     return ps2;

   }
}

/* intersection Arc-Transition */
QPointF Arc::intersectionPoint2(QGraphicsItem * rectangle, QLineF * line) const
{
    QPointF point, intersectPoint;
    QList<QLineF> list;

    QPainterPath shape = rectangle->mapToScene(rectangle->shape());
    QLineF line5(shape.elementAt(0).x, shape.elementAt(0).y,
            shape.elementAt(1).x, shape.elementAt(1).y);
    QLineF line6(shape.elementAt(1).x, shape.elementAt(1).y,
            shape.elementAt(2).x, shape.elementAt(2).y);
    QLineF line7(shape.elementAt(2).x, shape.elementAt(2).y,
            shape.elementAt(3).x, shape.elementAt(3).y);
    QLineF line8(shape.elementAt(3).x, shape.elementAt(3).y,
            shape.elementAt(4).x, shape.elementAt(4).y);

    list<<line5<<line6<<line7<<line8;

    foreach(QLineF l,list)
    if(line->intersect(l, &intersectPoint ) == QLineF::BoundedIntersection)
        point = intersectPoint;

    return point;
}
