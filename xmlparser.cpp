/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    xmlparser.cpp
**************************************************************/

#include "xmlparser.h"
#include <QDebug>

// return XML objects
PTNET_ATTR XmlParser::getXML_net() const
{
    return net;
}

/* begin parsing */
bool XmlParser::parseXML(const QString &xmlContent)
{
    QXmlStreamReader xml(xmlContent);

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::ProcessingInstruction)
            continue;

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "pnml")
                continue;

            if (xml.name() == "net")
            {
                if (xml.attributes().hasAttribute("id"))
                {
                    net.id = xml.attributes().value("id").toString();

                    if (!parseXML_Net(xml))
                        return false;

                    continue;
                }
            }
         }
    }

    if (xml.hasError())
    {
        qDebug() << "XML-Pseudocode parsing error: "<< xml.errorString();
        return false;
    }

    return true;
}

bool XmlParser::parseXML_Net(QXmlStreamReader &xml)
{
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "net")
            break;

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "name")
            {
                if (!parseXML_Name(xml))
                    return false;

                net.name = name;

                continue;
            }
            if (xml.name() == "page")
            {
                PAGE_ATTR page;

                if (xml.attributes().hasAttribute("id"))
                {
                    page.id = xml.attributes().value("id").toString();

                    if (!parseXML_Page(xml, page))
                        return false;

                	continue;
                }
            }
        }
    }

    return true;
}

bool XmlParser::parseXML_Page(QXmlStreamReader &xml, PAGE_ATTR &page)
{
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if ((token == QXmlStreamReader::EndElement) && (xml.name() == "page"))
        {
            net.pages << page;
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "name")
            {
                if (!parseXML_Name(xml))
                    return false;

                page.name = name;

                continue;
    	    } 
            if (xml.name() == "place")
            {
                if (xml.attributes().hasAttribute("id"))
                {
                    id = xml.attributes().value("id").toString();

                    if (!parseXML_Place(xml, page))
                        return false;

                    continue;
                }
            }
            if (xml.name() == "referencePlace")
            {
                if (xml.attributes().hasAttribute("id") && xml.attributes().hasAttribute("ref"))
                {
                    id = xml.attributes().value("id").toString();
                    ref = xml.attributes().value("ref").toString();

                    if (!parseXML_refPlace(xml, page))
                        return false;

                    continue;
                }
            }
            if (xml.name() == "transition")
            {
                if (xml.attributes().hasAttribute("id"))
                {
                    id = xml.attributes().value("id").toString();

                    if (!parseXML_Transition(xml, page))
                        return false;

                    continue;
                }
            }
            if (xml.name() == "referenceTransition")
            {
                if (xml.attributes().hasAttribute("id") && xml.attributes().hasAttribute("ref"))
                {
                    id = xml.attributes().value("id").toString();
                    ref = xml.attributes().value("ref").toString();

                    if (!parseXML_refTransition(xml, page))
                        return false;

                    continue;
                }
            }
            if (xml.name() == "arc")
            {
                if (xml.attributes().hasAttribute("id")
                    && xml.attributes().hasAttribute("source")
                    && xml.attributes().hasAttribute("target"))
                 {
                    id = xml.attributes().value("id").toString();                
                    source = xml.attributes().value("source").toString();
                    target = xml.attributes().value("target").toString();

                    if (!parseXML_Arc(xml, page))
                        return false;

                     continue;
                 }
            }
            continue;
        }
    }

    if (xml.hasError())
    {
        qDebug() << "XML-Pseudocode parsing error:- "<< xml.errorString();
        return false;
    }

    return true;

}

bool XmlParser::parseXML_Place(QXmlStreamReader &xml, PAGE_ATTR &page)
{
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "place")
        {
            PLACE_ATTR place;

            place.id = id;
            place.name = name;
            place.x = x;
            place.y = y;
            place.offsetx = offsetx;
            place.offsety = offsety;
            place.initmark = initmark;
            place.capacity = capacity;
            page.placeNodes << place;

            break;
        }
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "name")
            {
                if (!parseXML_Name(xml))
                    return false;

                continue;

            }else if (xml.name() == "graphics")
             {
                if (!parseXML_Graphics(xml)) return false;
                continue;

             }else if (xml.name() == "initialMarking")
             {
                if (!parseXML_InitialMarking(xml)) return false;
                continue;
             }else if (xml.name() == "toolspecific")
               {
                    if (!parseXML_ToolSpecific(xml)) return false;
                    continue;
               }
        }
    }

    return true;
}

bool XmlParser::parseXML_refPlace(QXmlStreamReader &xml, PAGE_ATTR &page)
{
    Q_UNUSED(page)

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        /*if (token == QXmlStreamReader::EndElement && xml.name() == "referencePlace")
        {
            REFPLACE_ATTR refplace;

            refplace.id = id;
            refplace.ref = ref;
            refplace.x = x;
            refplace.y = y;

            page.refPlaces << refplace;

            break;
        }*/
        if (token == QXmlStreamReader::StartElement)
        {
             if (xml.name() == "graphics")
             {
                if (!parseXML_Graphics(xml))
                    return false;

                continue;
             }
        }
    }

    return true;
}

bool XmlParser::parseXML_Transition(QXmlStreamReader &xml, PAGE_ATTR &page)
{
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "transition")
        {
            TRANSITION_ATTR transition;

            transition.id = id;
            transition.name = name;
            transition.x = x;
            transition.y = y;
            transition.offsetx = offsetx;
            transition.offsety = offsety;
            transition.rotation = rotation;

            page.transitionNodes << transition;

            break;
        }
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "name")
            {
                if (!parseXML_Name(xml))
                    return false;

                continue;

            } else if (xml.name() == "graphics")
            {
                if (!parseXML_Graphics(xml))
                    return false;

                continue;

            }else if (xml.name() == "toolspecific")
            {
                if (!parseXML_ToolSpecific(xml))
                    return false;

                continue;
            }
        }
    }

    return true;
}

bool XmlParser::parseXML_refTransition(QXmlStreamReader &xml, PAGE_ATTR &page)
{
    Q_UNUSED(page)

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        /*if (token == QXmlStreamReader::EndElement && xml.name() == "referenceTransition")
        {
            REFTRANSITION_ATTR reftransition;

            reftransition.id = id;
            reftransition.ref = ref;
            reftransition.x = x;
            reftransition.y = y;

            page.refTransitions << reftransition;

            break;
        }*/
        if (token == QXmlStreamReader::StartElement)
        {
             if (xml.name() == "graphics")
             {
                if (!parseXML_Graphics(xml))
                    return false;

                continue;
             }else if (xml.name() == "toolspecific")
              {
                if (!parseXML_ToolSpecific(xml))
                   return false;

                continue;
              }
        }
    }

    return true;
}

bool XmlParser::parseXML_Arc(QXmlStreamReader &xml, PAGE_ATTR &page)
{
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "arc")
        {
            ARC_ATTR arc;

            arc.id = id;
            arc.source = source;
            arc.target = target;
            arc.weight = weight;
            arc.points << points;
            points.clear();

            page.arcs << arc;
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "inscription")
            {
                if (!parseXML_Inscription(xml))
                    return false;

                continue;

            }
            if (xml.name() == "graphics")
            {
                if (!parseXML_Positions(xml))
                    return false;

                continue;

            }
        }
    }

    return true;

}

bool XmlParser::parseXML_Name(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "name")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "text")
            {
                name = getElementData(xml);
                continue;

            } else if (xml.name() == "graphics")
            {
                if (!parseXML_Graphics(xml))
                    return false;

                continue;

            }
        }
    }
    return true;
}

bool XmlParser::parseXML_Graphics(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "graphics")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "offset")
            {
                v.setValue(xml.attributes().value("x").toString());
                offsetx = v.toInt();
                v.setValue(xml.attributes().value("y").toString());
                offsety = v.toInt();
                    continue;
            }
            else if(xml.name() == "position")
            {
                v.setValue(xml.attributes().value("x").toString());
                x = v.toInt();
                v.setValue(xml.attributes().value("y").toString());
                y = v.toInt();
                    continue;
            }
       }
    }
    return true;
}

bool XmlParser::parseXML_InitialMarking(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "initialMarking")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "text")
            {
                v.setValue(getElementData(xml));
                initmark = v.toInt();

            }
            else if (xml.name() == "graphics")
            {
                if (!parseXML_Graphics(xml)) return false;
                continue;

            }
        }
    }
    return true;
}

bool XmlParser::parseXML_Inscription(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "inscription")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "text")
            {
                v.setValue(getElementData(xml));
                weight = v.toInt();

            }
        }
    }
    return true;

}

bool XmlParser::parseXML_Positions(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "graphics")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "position")
            {
                v.setValue(xml.attributes().value("x").toString());
                x = v.toFloat();
                v.setValue(xml.attributes().value("y").toString());
                y = v.toFloat();
                points<<QPointF(x,y);
                    continue;
            }
        }
    }
    return true;


}

bool XmlParser::parseXML_ToolSpecific(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "toolspecific")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "placeCapacity")
            {
                v.setValue(xml.attributes().value("capacity").toString());
                capacity = v.toInt();
                    continue;
            }
            else if(xml.name() == "rotation")
            {
                v.setValue(xml.attributes().value("degree").toString());
                rotation = v.toInt();
                    continue;
            }
       }
    }
    return true;

}

QString XmlParser::getElementData(QXmlStreamReader &xml) const
{
    /* We need a start element, like <name> */
    if (xml.tokenType() != QXmlStreamReader::StartElement)
    {
        return "";
    }

    xml.readNext();

    /* This elements needs to contain Characters so we know it's
     * actually data, if it's not we'll leave.     */
    if (xml.tokenType() != QXmlStreamReader::Characters)
    {
        return "";
    }

    /* Now we can return the data. */
    return xml.text().toString();
}

