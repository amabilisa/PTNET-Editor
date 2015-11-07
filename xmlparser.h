/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    xmlparser.h
**************************************************************/

#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QXmlStreamReader>
#include <QVariant>

#include "defs.h"

class XmlParser
{

public:

    explicit XmlParser(){}
    bool parseXML(const QString &xmlContent);
    PTNET_ATTR getXML_net() const;

private:

    bool parseXML_Net(QXmlStreamReader &xml);
    bool parseXML_Page(QXmlStreamReader &xml, PAGE_ATTR &page);
    bool parseXML_Place(QXmlStreamReader &xml, PAGE_ATTR &page);
    bool parseXML_refPlace(QXmlStreamReader &xml, PAGE_ATTR &page);
    bool parseXML_Transition(QXmlStreamReader &xml, PAGE_ATTR &page);
    bool parseXML_refTransition(QXmlStreamReader &xml, PAGE_ATTR &page);
    bool parseXML_Arc(QXmlStreamReader &xml, PAGE_ATTR &page);
    bool parseXML_Name(QXmlStreamReader &xml);
    bool parseXML_Graphics(QXmlStreamReader &xml);
    bool parseXML_Offset(QXmlStreamReader &xml);
    bool parseXML_Position(QXmlStreamReader &xml);
    bool parseXML_InitialMarking(QXmlStreamReader &xml);
    bool parseXML_Inscription(QXmlStreamReader &xml);
    bool parseXML_Positions(QXmlStreamReader &xml);
    bool parseXML_ToolSpecific(QXmlStreamReader &xml);

    QString getElementData(QXmlStreamReader& xml) const;

    QVariant v;
    QString id, name, source, target, ref;
    int offsetx, offsety, x, y, initmark, weight, capacity, rotation;
    QList<QPointF> points;

    PTNET_ATTR net;
    QList <PAGE_ATTR> pages;
};

#endif
