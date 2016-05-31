/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    graphvisualizer.cpp
**************************************************************/

#include "graphvisualizer.h"

#include <QDebug>

// 1 INCHE = 71.9999999 pixel (point)
#define INCHE 71.9999999
#define SCENE 5000
#define SCENEMID SCENE/2

GraphVisualizer::GraphVisualizer()
{
  setSceneRect(0, 0, SCENE, SCENE);
  setItemIndexMethod(NoIndex);
}

/* visualize the graph */
void GraphVisualizer::visualize_graph(
        Marking& init_Marking,
        QMap<QString, int> &cap_places, 
        QMap<QString, QString> places_names,
        QList<TRANS_RELATION> &tr_relations)
{
 GraphGenerator graphGen(init_Marking, cap_places, tr_relations);
 Graph g = graphGen.generate_graph();

//![0] clear the scene
 if(!items().isEmpty())
     erase_graph();

 
 placesNames = places_names;
 
//![1] Laying the graph using GraphViz library. See:
//! http://www.graphviz.org/doc/libguide/libguide.pdf
//! http://www.graphviz.org/pdf/Agraph.pdf
 QString graph_attrs = create_graph_layout();

//![2] Extract for each edge and node the list of attributes
// separated by single spaces within a QStringList
 QStringList attributes = graph_attrs.split("\n");
 attributes.removeFirst();
 attributes.removeLast();
 attributes.removeLast();

 QStringList nodes_attrs, edges_attrs;

 foreach(QString attr, attributes)
 {
     if(attr.at(0) == 'n')
         nodes_attrs << attr;
     else
         edges_attrs << attr;
 }

//![3]
  visualize_nodes (nodes_attrs, g);
//![4]
  visualize_edges (edges_attrs);
}

QString GraphVisualizer::create_graph_layout()
{
 Agraph_t * dot_graph; 

 FILE * fp;

 gvc = gvContext();

// graph.dot was created by : graphGen.generate_graph()
 fp = fopen("graph.dot", "r");

#ifdef WITH_CGRAPH
    dot_graph = agread(fp, 0);
#else
    dot_graph = agread(fp);
#endif
    
  agsafeset(dot_graph, (char*)"overlap", (char*)"scalexy", (char*)"");
  agsafeset(dot_graph, (char*)"splines", (char*)"true", (char*)"");
  agsafeset(dot_graph, (char*)"pad", (char*)"0,2", (char*)"");
  agsafeset(dot_graph, (char*)"dpi", (char*)"96,0", (char*)"");
  agsafeset(dot_graph, (char*)"sep",(char*)"+25,25", (char*)"");
  agsafeset(dot_graph, (char*)"nodesep", (char*)"0.5", (char*)"");
  agsafeset(dot_graph, (char*)"rankdir", (char*)"BT", (char*)"");
  agsafeset(dot_graph, (char*)"root", (char*)"0", (char*)"");
  agsafeset(dot_graph, (char*)"rank", (char*)"same", (char*)"");
  agsafeset(dot_graph, (char*)"labeldistance", (char*)"1.2", (char*)"");

// Laying out the graph using a graph layout algo: dot, neato, fdp, sfdp
 gvLayout(gvc, dot_graph, "dot");
// attaches the computed position information to the nodes and edges and output the rendering to character buffer
 unsigned int len;
 char *buffer;
 gvRenderData(gvc, dot_graph, "plain", &buffer, &len);
// The buffer contains the node and edges attributes in plain output format.
 QString graph_attr(buffer);
 gvFreeRenderData(buffer);
 gvFreeLayout(gvc, dot_graph);
 agclose(dot_graph);
 fclose(fp);
  
 return graph_attr;
}

/* Visualize nodes*/
void GraphVisualizer::visualize_nodes(QStringList &nodes_attrs, const Graph& g)
{
 Graph G = g;
 nodes_markings_map markings = get(vertex_marking, G);
 foreach (QString node_attrs, nodes_attrs)
 {
   QStringList attrs = node_attrs.split(" ");
   QVariant v(attrs[1]);
   int id = v.toInt();
   Marking M = markings[id];
   visualize_node(attrs, M);
 }
}

/* visualize node */
void GraphVisualizer::visualize_node(const QStringList& attrs, const Marking& M)
{
 QVariant v(attrs[1]);
 int id = v.toInt();
// x coord of the node's shape's center in inche
 v.setValue(attrs[2]);
 float x = v.toFloat() * INCHE;
// y coord of the node's shape's center in inche
 v.setValue(attrs[3]);
 float y = v.toFloat() * INCHE;
// the node's shape's width in inche
 v.setValue(attrs[4]);
 float wd = v.toFloat() * INCHE;
// the node's shape's height in inche
 v.setValue(attrs[5]);
 float ht = v.toFloat() * INCHE;

 // M maps places id to their marks. But we want to display, on the graphnode 
 // infoball, places by their names not by their id:  
   QList<NODELABEL> M1;
   QMapIterator<QString, int> p1(M);
   while (p1.hasNext())
   {
     p1.next();
     int mark = p1.value();
     QString name = placesNames.value(p1.key());
     NODELABEL ndlabel = {name, mark};
     M1 << ndlabel;
   }
 
// create the graphnode 
 GraphNode * item = new GraphNode(id, M1, wd, ht);
 item->setPos(x + SCENEMID - wd/2, y + SCENEMID - ht/2);
 addItem(item);
}

/* draw edges */
void GraphVisualizer::visualize_edges(QStringList &edges_attrs)
{
 int index = 0;
 foreach (QString edge_attrs, edges_attrs)
 {
    QStringList attrs = edge_attrs.split(" ");
    visualize_edge(attrs, index++);
 }
}

/* draw edge */
void GraphVisualizer::visualize_edge(const QStringList &attrs, int index)
{
 // the edge's tail (source) node's id
 QVariant v(attrs[1]);
 int src = v.toInt();
 // the edge's head (target) node's id
 v.setValue(attrs[2]);
 int trg = v.toInt();
 //the number of the edg's spline control points
 v.setValue(attrs[3]);
 int n = v.toInt();

 // get the control points list.
 // A spline curve with n control points
 // contains (n-1)/3 Bezier curve
 QList<QPointF> points = edge_control_points(attrs, n);

 // get the edge's label's text
 QString label = attrs[4+2*n];
 // get the label's x coordinate
 v.setValue(attrs[5+2*n]);
 float lx = v.toFloat()*INCHE + SCENEMID;
 // get the label's y coordinate
 v.setValue(attrs[6+2*n]);
 float ly = v.toFloat()*INCHE + SCENEMID;

 // get source and target nodes
 GraphNode * source = 0;
 GraphNode * target = 0;

 foreach(QGraphicsItem * item, items())
    {
        if(item->type() == GraphNode::Type)
        {
            GraphNode * node = qgraphicsitem_cast<GraphNode*>(item);
            int id = node->getIndex();
            if(id == src)
                source = node;
            if(id == trg)
                target = node;
        }
    }

 points.replace(0, source->sceneBoundingRect().center());
 points.replace(points.size()-1, target->sceneBoundingRect().center());
 
 // construct the edge's curve
 QPainterPath curve = create_edge_curve(points);

 // create the edge item and add it to the scene
 GraphEdge * edge = new GraphEdge(source, target, label, 
	curve, QPointF(lx,ly), index);
 addItem(edge);
 source->addOutEdge(edge);
 target->addInEdge(edge);
}

QList<QPointF> GraphVisualizer::edge_control_points(const QStringList &attrs, int n)
{
    int i=4;
    QList<QPointF> points;
    while(i <= (3+2*n))
    {
        QVariant v(attrs[i]);
        float x = v.toFloat();
        i++;
        v.setValue(attrs[i]);
        float y = v.toFloat();
        i++;
        // x and y are in INCHE. The scene is SCENEx5OOO points
        points << QPointF(x*INCHE +SCENEMID,y*INCHE +SCENEMID);
    }
 return points;
}

QPainterPath GraphVisualizer::create_edge_curve(const QList<QPointF>& points)
{  
  int k=0, i=0;
  QPainterPath curve;
  curve.moveTo(points[0]);

    while(i<((points.size()-1)/3))
    {
        curve.cubicTo(points[k+1],points[k+2],points[k+3]);
        i++;
        k+=3;
    }

  return curve;
}

// delete all nodes and edges and free memory
void GraphVisualizer::erase_graph()
{
 QList<QGraphicsItem*> itms = items();

 foreach(QGraphicsItem * item, itms)
    if(item->type() == QGraphicsSimpleTextItem::Type)
        itms.removeOne(item);

 foreach(QGraphicsItem * item, itms)
 {
    if(item->type() == GraphEdge::Type)
     {
        GraphEdge * edge = qgraphicsitem_cast<GraphEdge*>(item);
            int index = edge->getIndex();
        GraphNode * sourceNode = qgraphicsitem_cast<GraphNode*>(edge->getSourceNode());
            sourceNode->removeOutEdge(index);
        GraphNode * targetNode = qgraphicsitem_cast<GraphNode*>(edge->getTargetNode());
            targetNode->removeInEdge(index);

        itms.removeOne(item);
        removeItem(item);
        delete item;
	item=0;
     }
 }

 foreach(QGraphicsItem * item, itms)
 {
    removeItem(item);
    delete item;
    item = 0;
 }

}

GraphVisualizer::~GraphVisualizer()
{

}
