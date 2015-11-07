/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    place.h
**************************************************************/

#ifndef PLACE_H
#define PLACE_H

#include <QGraphicsEllipseItem>

#include "arc.h"

class Place : public QGraphicsEllipseItem
{
 public:

    enum { Type = UserType + 1 };

    explicit Place(const QString &id);
    Place(const PLACE_ATTR &place);
    ~Place ();

    void createPlace();
    PLACE_ATTR toXml() const;

    void addInputArc(QGraphicsItem * arc);
    void addOutputArc(QGraphicsItem * arc);
    void deleteArc(QString id);

    int getTokens() const;
    void setTokens (int tok);
    void updateTokens(int tok);
    int getCapacity() const;
    void setCapacity(int c);
    QString getName () const;
    void setName (const QString& nm);
    QString getId () const;
    void setLabel_1();
    void setLabel_2();

    bool reachCapacity(Arc * arc);
    bool hasRelations ();

    int type () const;
    QRectF boundingRect() const;
    QPainterPath shape () const;
    QVariant itemChange (GraphicsItemChange change, const QVariant &value);
    bool collidesWithItem ( const QGraphicsItem * other,
	 Qt::ItemSelectionMode mode ) const;

 protected:

    void paint ( QPainter * painter, 
	const QStyleOptionGraphicsItem * option, 
		QWidget * widget );

 private:

    QString id;
    QString name;
    int tokens;
    int capacity;

    QGraphicsSimpleTextItem * label;

    QList<Arc *> input;
    QList<Arc *> output;
    
};

#endif // PLACE_H
