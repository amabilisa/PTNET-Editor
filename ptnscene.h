/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    ptnscene.h
**************************************************************/

#ifndef PTNSCENE_H
#define PTNSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

#include "place.h"
#include "transition.h"
#include "arc.h"
#include "sceneselectionrectangle.h"

class PTNscene : public QGraphicsScene
{
    Q_OBJECT

public:

    explicit PTNscene(QObject * parent = 0);
    ~PTNscene(){}
	
    void setMode (int mode);
    void removeItems();
    void enableSelection (bool select);
    void trakInitialMarking ();
    void resetInitialMarking();

    void from_Xml (const QList<PAGE_ATTR> &pages);
    void addXML_places (const QList <PLACE_ATTR> &places);
    void addXML_transitions (const QList <TRANSITION_ATTR> &transitions);
    void addXML_arcs (const QList <ARC_ATTR> &arcs);

    Marking getInitialMarking () const;
    QMap<QString, int> getPlacesCapacities ();
    QList<TRANS_RELATION> getRelations ();

signals:

    void nodeInserted(const QPointF &itemPos, const QString &id);
    void arcInserted(QGraphicsItem * source, QGraphicsItem * target, 
	const QPainterPath &arc_path, const QString &id, PTNscene * scene, int w =1);
    void itemMoved (QGraphicsItem * movedItem, const QPointF &oldPosition);
    void nodeRemoved (QGraphicsItem * item, PTNscene * scene);
    void arcRemoved (QGraphicsItem * item, PTNscene * scene);
    void nodesInserted (const QStringList &places_names);
    void itemDoubleClicked(QGraphicsItem * item);

protected:

    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void keyPressEvent ( QKeyEvent * keyEvent );
    //void drawBackground ( QPainter * painter, const QRectF & rect);

private:

    int places_indexs;
    int transitions_indexs;
    int arcs_indexs;
    int mode;

    QGraphicsItem     * currentItem;
    QGraphicsPathItem * pathitem;
    
    SceneSelectionRectangle * selectionRect;

    QList<QPointF> points;
    QPointF origin, oldPos, currentPos;

    Marking initial_marking;
};

#endif // PTNSCENE_H
