/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    transition.h
**************************************************************/

#ifndef TRANSITION_H
#define TRANSITION_H

#include "place.h"
#include "arc.h"

class Transition : public QGraphicsRectItem
{
 public:

    enum { Type = UserType + 2 };

    explicit Transition(const QString &id);
    Transition(const TRANSITION_ATTR &transition);
    ~Transition ();

    void createTransition();
    TRANSITION_ATTR toXml() const;

    void showEditDialog ();
    void setAttributes ();

    QString getId () const;
    QString getName () const;
    void setName (const QString& nm);
    void setMode (int mod);

    void addInputArc(QGraphicsItem * arc);
    void addOutputArc(QGraphicsItem * arc);
    void deleteArc(QString id);

    bool isFirable();
    void fire();

    bool hasRelations ();
    TRANS_RELATION getTrans_Relations() const;

    /* @;;;; */
    int type () const;
    QRectF boundingRect() const;
    QPainterPath shape () const;
    QVariant itemChange (GraphicsItemChange change, const QVariant &value);
    bool collidesWithItem ( const QGraphicsItem * other, Qt::ItemSelectionMode mode ) const;

    void setRotation(int degree);
    int getRotation() const;

 protected:

    void paint ( QPainter * painter, 
	const QStyleOptionGraphicsItem * option, 
		QWidget * widget );

 private:

    QString id;
    QString name;
    int rotation;    

    QGraphicsSimpleTextItem * label;

    QList<Arc *> input;
    QList<Arc *> output;

    int mode;
    QColor color;
};

#endif // TRANSITION_H
