/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    place.cpp
**************************************************************/

#include "place.h"

Place::Place(const QString &id)
{
    this->id = id;
    name = id;
    tokens = 0;
    capacity = 0;

    createPlace();

    label->setPos(30, 30);
}

/* From XML */
Place::Place(const PLACE_ATTR &place)
{
    id = place.id;

    if(place.name.isNull())
        name = id;
    else
        name = place.name;

    tokens = place.initmark;

    capacity = place.capacity;

    createPlace();

    label->setPos(place.offsetx, place.offsety);
}

void Place::createPlace()
{
    setRect(0, 0, place_diameter, place_diameter);

    setZValue(1000.0);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    label = new QGraphicsSimpleTextItem(this);
    label->setFlag(QGraphicsItem::ItemIsMovable, true);
    label->setFlag(QGraphicsItem::ItemIsSelectable, true);
    label->setText(name);   
}

/* return place attributes as a structure */
PLACE_ATTR Place::toXml() const
{
  PLACE_ATTR place;

  place.id = id;
  place.name = name;
  place.initmark = tokens;
  place.capacity = capacity;
  place.x = pos().x();
  place.y = pos().y();
  place.offsetx = label->x();
  place.offsety = label->y();

  return place;
}

/* add input arc */
void Place::addInputArc(QGraphicsItem * arc)
{
   input << qgraphicsitem_cast<Arc*>(arc);
}

/* add output arc */
void Place::addOutputArc(QGraphicsItem * arc)
{
   output << qgraphicsitem_cast<Arc*>(arc);
}

/* delete Arc */
void Place::deleteArc(QString id)
{
    for(int i=0; i < input.size(); i++)
    {
        if(input[i]->getId() == id)
        {
            input.removeAt(i);
            return;
        }
    }

    for(int i=0; i < output.size(); i++)
    {
        if(output[i]->getId() == id)
        {
            output.removeAt(i);
            return;
        }
    }
}

/* update tokens */
void Place::updateTokens(int tok)
{
    if((tok<0)&&(tokens==0))
            return;

    tokens += tok;
}

void Place::setTokens (int tok)
{
    tokens = tok;
}

/* get tokens */
int Place::getTokens()  const
{
  return tokens;
}

/* get capacity */
int Place::getCapacity() const
{
  return capacity;
}

void Place::setCapacity(int c)
{
    capacity = c;
}

/* get name */
QString Place::getName ()  const
{
    return name;
}

/* set name */
void Place::setName (const QString& nm)
{
    name = nm;
}

/* get id */
QString Place::getId ()  const
{
    return id;
}

void Place::setLabel_1()
{
   label->setText(name);
}

void Place::setLabel_2()
{
    QString lb;

       if(capacity == 0)
        {
            lb = QString (name+"\n"+"k = "+QObject::trUtf8("\u221e"));
        }
        else
        {
            QVariant v(capacity);
            lb = QString (name+"\n"+"k = "+v.toString());
        }

   label->setText(lb);
}

/* Check if the place reach capacity with connection "arc" */
bool Place::reachCapacity(Arc * arc)
{
  if(capacity == 0)
      return false;
  else if(arc->getWeight()+tokens > capacity)
      return true;
  else
      return false;
}

bool Place::hasRelations ()
{
    if (input.isEmpty() && output.isEmpty())
        return false;
    else
        return true;
}

int Place::type () const
{
    return Type;
}

QRectF Place::boundingRect() const
{
    qreal a = (pen().width())/2;
    return QRectF(0, 0, place_diameter, place_diameter)
            .normalized()
            .adjusted(-a, -a, a, a);
}

QPainterPath Place::shape () const
{
    QPainterPath shape;
    shape.addEllipse(0, 0, place_diameter , place_diameter);
    return shape;
}

QVariant Place::itemChange (GraphicsItemChange change, const QVariant &value)
{

    if ((change == QGraphicsItem::ItemPositionChange)
	||(change == QGraphicsItem::ItemPositionHasChanged))
    {
        foreach (Arc * inarc, input)
            inarc->updatePosition();

        foreach (Arc * outarc, output)
            outarc->updatePosition();
    }

    return value;
}

void Place::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option,
			 QWidget * widget )
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QColor PenColor;
    QColor BrushColor;

    if((input.isEmpty()) && (output.isEmpty()))
    {
        PenColor = Qt::darkRed;
        BrushColor = QColor(255, 240, 240);
    }
    else if(isSelected())
    {
        foreach(Arc * arc, input)
            arc->setSelected(true);
        foreach(Arc * arc, output)
            arc->setSelected(true);

        PenColor = Qt::blue;
        BrushColor = QColor(240, 240, 255);
    }
    else
    {
        PenColor = Qt::black;
        BrushColor = Qt::white;
    }


    painter->setPen (QPen(PenColor, 1, Qt::SolidLine,
	 Qt::RoundCap, Qt::MiterJoin));
    label->setBrush (PenColor);
    painter->setBrush (BrushColor);
    painter->setRenderHint (QPainter::Antialiasing);
    painter->drawEllipse (0, 0, place_diameter, place_diameter);

    painter->setBrush (PenColor);

    if(tokens == 1)
     painter->drawEllipse(19, 19, 4, 4);
    else if(tokens == 2)
    {
        painter->drawEllipse(20, 20, 4, 4);
        painter->drawEllipse(6, 6, 4, 4);
    }
    else if(tokens == 3)
    {
        painter->drawEllipse(20, 20, 4, 4);
        painter->drawEllipse(13, 13, 4, 4);
        painter->drawEllipse(6, 6, 4, 4);
    }
    else if(tokens == 4)
    {
        painter->drawEllipse(20, 20, 4, 4);
        painter->drawEllipse(6, 6, 4, 4);
        painter->drawEllipse(6, 20, 4, 4);
        painter->drawEllipse(20, 6, 4, 4);
    }
    else if(tokens == 5)
    {
        painter->drawEllipse(20, 20, 4, 4);
        painter->drawEllipse(6, 6, 4, 4);
        painter->drawEllipse(13, 13, 4, 4);
        painter->drawEllipse(6, 20, 4, 4);
        painter->drawEllipse(20, 6, 4, 4);
    }
    else if(tokens == 6)
    {
        painter->drawEllipse(20, 20, 4, 4);
        painter->drawEllipse(6, 6, 4, 4);
        painter->drawEllipse(6, 20, 4, 4);
        painter->drawEllipse(20, 6, 4, 4);
        painter->drawEllipse(6, 13, 4, 4);
        painter->drawEllipse(20, 13, 4, 4);
    }
    else if(tokens == 7)
    {
        painter->drawEllipse(20, 20, 4, 4);
        painter->drawEllipse(6, 6, 4, 4);
        painter->drawEllipse(6, 20, 4, 4);
        painter->drawEllipse(20, 6, 4, 4);
        painter->drawEllipse(6, 13, 4, 4);
        painter->drawEllipse(20, 13, 4, 4);
        painter->drawEllipse(13, 13, 4, 4);
    }
    else if(tokens == 8)
    {
        painter->drawEllipse(20, 20, 4, 4);
        painter->drawEllipse(6, 6, 4, 4);
        painter->drawEllipse(6, 20, 4, 4);
        painter->drawEllipse(20, 6, 4, 4);
        painter->drawEllipse(6, 13, 4, 4);
        painter->drawEllipse(20, 13, 4, 4);
        painter->drawEllipse(13, 6, 4, 4);
        painter->drawEllipse(13, 20, 4, 4);
    }

    else if(tokens == 9)
    {
        painter->drawEllipse(20, 20, 4, 4);
        painter->drawEllipse(6, 6, 4, 4);
        painter->drawEllipse(6, 20, 4, 4);
        painter->drawEllipse(20, 6, 4, 4);
        painter->drawEllipse(6, 13, 4, 4);
        painter->drawEllipse(20, 13, 4, 4);
        painter->drawEllipse(13, 13, 4, 4);
        painter->drawEllipse(13, 6, 4, 4);
        painter->drawEllipse(13, 20, 4, 4);
    }
    else if(tokens > 9)
    {
        QVariant v(tokens);
        if(tokens < 100)
            painter->drawText(7, 20, QString(v.toString()));
        else
            painter->drawText(4, 20, QString(v.toString()));
    }

}

bool Place::collidesWithItem ( const QGraphicsItem * other, Qt::ItemSelectionMode mode ) const
{
    Q_UNUSED(mode);
    QPainterPath path1 = this->mapFromItem(other, other->shape());
    return path1.intersects(this->shape());
}

Place::~Place ()
{
    delete label;
}

