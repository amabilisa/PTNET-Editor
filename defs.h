/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    defs.h
**************************************************************/

#ifndef DEFS_H
#define DEFS_H

#include <QList>
#include <QPointF>
#include <QMap>

#define omega 9999999
#define place_diameter 30
#define transition_width 30
#define transition_heigh 8

typedef QMap<QString, int> Marking;

enum{normalMode=0, animationMode=1, addPlaceMode=2, \
            addTransMode=3,drawArcMode=4, addToken=5, subToken=6};

typedef struct{
     QString id, name;
     /* coordinates */
     int x, y;
     int initmark, capacity;
     /* label offset */
     int offsetx, offsety;
   } PLACE_ATTR;

/* typedef struct
    {
        QString id, ref;
        int x, y, rotation;
    }; REFTRANS_ATTR */

typedef struct{
     QString id, name;
     /* coordinate */
     int x, y;
     int rotation;
     /* label coordinate */
     int offsetx, offsety;
   } TRANSITION_ATTR;

/* typedef struct
    {
        QString id, ref;
        int x, y, rotation;
    }; REFTRANS_ATTR */

typedef struct{
     QString id, source, target;
     int weight;
     QList<QPointF> points;
   } ARC_ATTR;


typedef struct{
     QString id, name;
     QList <PLACE_ATTR> placeNodes;
     /* QList <REFPLACE_ATTR> refPlaces;*/
     QList <TRANSITION_ATTR> transitionNodes;
     /* QList <REFTRANS_ATTR> refTransitions;*/
     QList <ARC_ATTR> arcs;
   } PAGE_ATTR;

typedef struct{
     QString id, name;
     QList <PAGE_ATTR> pages;
   } PTNET_ATTR;

typedef struct{
    QString name;
    QMap<QString, int> preSet;
    QMap<QString, int> postSet;
  } TRANS_RELATION;
 
#endif 
