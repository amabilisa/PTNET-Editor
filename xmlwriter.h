/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    xmlwriter.h
**************************************************************/

#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QVariant>
#include <QFile>
#include <QXmlStreamWriter>
#include <QDebug>

#include "defs.h"

class XmlWriter
{

 public:

    explicit XmlWriter(const PTNET_ATTR &net);

    bool writeXML(QFile * xmlContent);
    bool writePage(QXmlStreamWriter &xml, PAGE_ATTR page);
    bool writePlaceNode(QXmlStreamWriter &xml, PLACE_ATTR place);
    /*bool writeRefPlaceNode(QXmlStreamWriter &xml, REFPLACE_ATTR refPlace);*/
    bool writeTransitionNode(QXmlStreamWriter &xml, TRANSITION_ATTR transition);
   /* bool writeRefTransitionNode(QXmlStreamWriter &xml, REFTRANSITION_ATTR refTransition);*/
    bool writeArc(QXmlStreamWriter &xml, ARC_ATTR arc);

 private:

    PTNET_ATTR ptnet;
    QString netname;
    QVariant v;
    QString id, name, source, target;
    int offsetx, offsety, x, y, initmark, weight;

};

#endif 
