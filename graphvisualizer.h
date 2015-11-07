/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    graphvisualizer.h
**************************************************************/

#ifndef GRAPHVISUALIZER_H
#define GRAPHVISUALIZER_H

#include "graphnode.h"
#include "graphedge.h"
#include "graphgenerator.h"

class GraphVisualizer : public QGraphicsScene
{

 public:

    explicit GraphVisualizer();
    ~GraphVisualizer();
    
    void visualize_graph (Marking& init_Marking,
                          QMap<QString, int> &cap_places,
                          QList<TRANS_RELATION> &tr_relation);
    void erase_graph ();
    QString create_graph_layout();
    void visualize_nodes (QStringList &nodes_attrs, const Graph& g);
    void visualize_node(const QStringList& attrs, const Marking& M);
    void visualize_edges (QStringList &edges_attrs);
    void visualize_edge(const QStringList &attrs, int index);
    QList<QPointF> edge_control_points(const QStringList &attrs, int n);
    QPainterPath create_edge_curve(const QList<QPointF>& points);

 private:

};

#endif // GRAPHVISUALIZER_H


