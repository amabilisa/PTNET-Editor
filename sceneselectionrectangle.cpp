/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    sceneselectionrectangle.cpp
**************************************************************/

#include "sceneselectionrectangle.h"

SceneSelectionRectangle::SceneSelectionRectangle()
	:QGraphicsRectItem()
{

  setZValue(2000.0);

}

void SceneSelectionRectangle::paint ( QPainter * painter, 
	const QStyleOptionGraphicsItem * option, QWidget * widget )
{
  Q_UNUSED(option);
  Q_UNUSED(widget);

  painter->setPen(QPen(Qt::darkBlue, 1,
        Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
  painter->setBrush(QColor(0, 0, 255, 20));
  painter->drawRect(rect());
}
 
 
