/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    sceneselectionrectangle.h
**************************************************************/

#ifndef __SCENESELECTIONRECTANGLE_H
#define __SCENESELECTIONRECTANGLE_H

#include <QPainter>
#include <QGraphicsRectItem>

class SceneSelectionRectangle : public QGraphicsRectItem
{
 public:
    SceneSelectionRectangle();

 protected:
	void paint ( QPainter * painter, 
		const QStyleOptionGraphicsItem * option, 
              QWidget * widget );

};

#endif 
 
