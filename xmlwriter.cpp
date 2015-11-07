/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    xmlwriter.cpp
**************************************************************/

#include "xmlwriter.h"

#include <QDebug>
    
XmlWriter::XmlWriter(const PTNET_ATTR &net)
{
    ptnet = net;
}

//![0]
bool XmlWriter::writeXML(QFile * xmlContent)
{
    QXmlStreamWriter xml(xmlContent);
    xml.setAutoFormatting(true);

    xml.writeStartDocument();
    xml.writeStartElement("pnml");
    xml.writeDefaultNamespace("http://www.pnml.org/version-2009/grammar/pnml");

     xml.writeStartElement("net");
     xml.writeAttribute("id", ptnet.id);
     xml.writeAttribute("type", "http://www.pnml.org/version-2009/grammar/ptnet"); 


        xml.writeStartElement("name");
            xml.writeTextElement("text", ptnet.name);
        xml.writeEndElement();

        foreach(PAGE_ATTR page, ptnet.pages)
        {
            if(!writePage(xml, page))
                qDebug()<<"Error ...";
        }

     xml.writeEndElement();
     /* </net> */

    xml.writeEndElement();
   /* </pnml> */

   xml.writeEndDocument();

  if (xml.hasError ())
	return false;

  return true;
}
//![0]

//![1]
/* write page */
bool XmlWriter::writePage(QXmlStreamWriter &xml, PAGE_ATTR page)
{
    /* <page id="pagexx"> */
    xml.writeStartElement("page");
    xml.writeAttribute("id", page.id);

    xml.writeStartElement("name");
        xml.writeTextElement("text", page.name);
    xml.writeEndElement();


        foreach(PLACE_ATTR place, page.placeNodes)
        {
            if(!writePlaceNode(xml, place))
                qDebug()<<"Error ...";
        }

        /* foreach(RefPlaceNode refPlace, page.refPlaces)
        {
            if(!writeRefPlaceNode(xml, refPlace))
                qDebug()<<"Error ...";
        }*/

        foreach(TRANSITION_ATTR transition, page.transitionNodes)
        {
            if(!writeTransitionNode(xml, transition))
                qDebug()<<"Error ...";
        }

        /* foreach(RefTransitionNode refTransition, page.refTransitions)
        {
            if(!writeRefTransitionNode(xml, refTransition))
                qDebug()<<"Error ...";
        }*/

        foreach(ARC_ATTR arc, page.arcs)
        {
             if(!writeArc(xml, arc))
                qDebug()<<"Error ...";
        }

    xml.writeEndElement();
    /* </page>*/

    if (xml.hasError ())
      return false;

     return true;
}

/* write place */
bool XmlWriter::writePlaceNode(QXmlStreamWriter &xml, PLACE_ATTR place)
{
   QVariant v;
   v.setValue(place.x);
   QString x = v.toString();
   v.setValue(place.y);
   QString y = v.toString();
   v.setValue(place.offsetx); 
   QString offsetx = v.toString();
   v.setValue(place.offsety);
   QString offsety = v.toString();
   v.setValue(place.initmark);
   QString initmark = v.toString();   
   v.setValue(place.capacity);
   QString capacity = v.toString();

   /* <place id="xx"> */
   xml.writeStartElement("place");
   xml.writeAttribute("id", place.id);

	/*<name>*/
	xml.writeStartElement("name");
	    xml.writeTextElement("text", place.name);
	    xml.writeStartElement("graphics");
		xml.writeEmptyElement("offset"); 
		xml.writeAttribute("x", offsetx);
		xml.writeAttribute("y", offsety);
	    xml.writeEndElement();
	xml.writeEndElement();
	/*</name>*/

	/* <toolspecific> */
	xml.writeStartElement("toolspecific");
	    xml.writeAttribute("tool", "petrinet");
	    xml.writeAttribute("version", "1.0");
	    xml.writeEmptyElement("placeCapacity");
	    xml.writeAttribute("capacity", capacity);
	xml.writeEndElement();
	/* </toolspecific> */

	xml.writeStartElement("graphics");
	    xml.writeEmptyElement("position"); 
	    xml.writeAttribute("x", x);
	    xml.writeAttribute("y", y);
	xml.writeEndElement();
  
	/* <initialMarking> */
	xml.writeStartElement("initialMarking");
	    xml.writeTextElement("text", initmark);
	    /*xml.writeStartElement("graphics");
		xml.writeEmptyElement("offset"); 
		xml.writeAttribute("x", offsetx);
		xml.writeAttribute("y", offsety);
	    xml.writeEndElement();*/
	xml.writeEndElement();

  xml.writeEndElement();
  /*</place>*/

  if (xml.hasError ())
	return false;

   return true;
}

/* write reference place */
/*bool XmlWriter::writeRefPlaceNode(QXmlStreamWriter &xml, REFPLACE_ATTR refPlace)
{
    QVariant v;
    v.setValue(refPlace.x);
    QString x = v.toString();
    v.setValue(refPlace.y);
    QString y = v.toString();

    // <referncePlace id="xxx" ref="xxx">
    xml.writeStartElement("referencePlace");
    xml.writeAttribute("id",  refPlace.id);
    xml.writeAttribute("ref", refPlace.ref);

    xml.writeStartElement("graphics");
         xml.writeEmptyElement("position");
         xml.writeAttribute("x", x);
         xml.writeAttribute("y", y);
    xml.writeEndElement();

   xml.writeEndElement();
   //</referencePlace>

   if (xml.hasError ())
     return false;

    return true;
}*/

/* write transition */
bool XmlWriter::writeTransitionNode(QXmlStreamWriter &xml, TRANSITION_ATTR transition)
{
   QVariant v;
   v.setValue(transition.x);
   QString x = v.toString();
   v.setValue(transition.y);
   QString y = v.toString();
   v.setValue(transition.offsetx); 
   QString offsetx = v.toString();
   v.setValue(transition.offsety);
   QString offsety = v.toString();
   v.setValue(transition.rotation);
   QString rotation = v.toString();

   xml.writeStartElement("transition");
   xml.writeAttribute("id", transition.id);

	/*<name>*/
	xml.writeStartElement("name");
	    xml.writeTextElement("text", transition.name);
	    xml.writeStartElement("graphics");
		xml.writeEmptyElement("offset"); 
		xml.writeAttribute("x", offsetx);
		xml.writeAttribute("y", offsety);
	    xml.writeEndElement();
	xml.writeEndElement();
	/*</name>*/

	  /* <toolspecific> */
	  xml.writeStartElement("toolspecific");
	    xml.writeAttribute("tool", "petrinet");
	    xml.writeAttribute("version", "1.0");
	    xml.writeEmptyElement("rotation");
	    xml.writeAttribute("degree", rotation);
	  xml.writeEndElement();
	  /* </toolspecific> */

	xml.writeStartElement("graphics");
	    xml.writeEmptyElement("position"); 
	    xml.writeAttribute("x", x);
	    xml.writeAttribute("y", y);
	xml.writeEndElement();
  
  xml.writeEndElement();
  /*</transition>*/

  if (xml.hasError ())
	return false;

   return true;
}

/* write ref transition */
/*bool XmlWriter::writeRefTransitionNode(QXmlStreamWriter &xml, REFTRANSITION_ATTR refTransition)
{
    QVariant v;
    v.setValue(refTransition.x);
    QString x = v.toString();
    v.setValue(refTransition.y);
    QString y = v.toString();
    v.setValue(refTransition.rotation);
    QString rotation = v.toString();

    // <referenceTransition id="xxx" ref="xxx">
    xml.writeStartElement("referenceTransition");
    xml.writeAttribute("id",  refTransition.id);
    xml.writeAttribute("ref", refTransition.ref);

    xml.writeStartElement("graphics");
         xml.writeEmptyElement("position");
         xml.writeAttribute("x", x);
         xml.writeAttribute("y", y);
    xml.writeEndElement();

    // <toolspecific>
    xml.writeStartElement("toolspecific");
      xml.writeAttribute("tool", "petrinet");
      xml.writeAttribute("version", "1.0");
      xml.writeEmptyElement("rotation");
      xml.writeAttribute("degree", rotation);
    xml.writeEndElement();
    // </toolspecific>

   xml.writeEndElement();
   //</referenceTransition>

   if (xml.hasError ())
     return false;

    return true;
}*/

/* write arc */
bool XmlWriter::writeArc(QXmlStreamWriter &xml, ARC_ATTR arc)
{
    QVariant v(arc.weight);

    xml.writeStartElement("arc");
    xml.writeAttribute("id", arc.id);
    xml.writeAttribute("source", arc.source);
    xml.writeAttribute("target", arc.target);

	/* <inscription> */
	xml.writeStartElement("inscription");
	    xml.writeTextElement("text", v.toString());
	xml.writeEndElement();
  
    if(!arc.points.isEmpty())
    {
        /* <graphics> */
        xml.writeStartElement("graphics");

        foreach(QPointF p, arc.points)
        {
            xml.writeEmptyElement("position");
                v.setValue(p.x());
            xml.writeAttribute("x", v.toString());
                v.setValue(p.y());
            xml.writeAttribute("y", v.toString());
        }

        xml.writeEndElement();
        /* </graphics> */
    }

    xml.writeEndElement();
    /* </arc> */

    if (xml.hasError ())
        return false;

    return true;
}
