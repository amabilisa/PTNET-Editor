#ifndef BOOST_GRAPH_H
#define BOOST_GRAPH_H

#include <utility>
#include <iostream>
#include <fstream>
#include <vector>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>



enum vertex_marking_t {
    vertex_marking
};

namespace boost {
  BOOST_INSTALL_PROPERTY(vertex, marking);
}

typedef  boost::property<vertex_marking_t, Marking> VertexProperty;
typedef  boost::property< boost::edge_name_t, std::string> EdgeProperty;

typedef  boost::adjacency_list< boost::vecS,  boost::vecS,  boost::bidirectionalS,\
        VertexProperty,  EdgeProperty> Graph;

typedef  boost::property_map<Graph, vertex_marking_t>::type nodes_markings_map;
typedef  boost::graph_traits<Graph>::vertex_descriptor g_node_descriptor;
typedef  boost::property_map<Graph,  boost::edge_name_t>::type edges_names_map;
typedef  boost::graph_traits<Graph>::edge_descriptor g_edge_descriptor;
typedef  boost::graph_traits<Graph>::vertex_iterator g_node_iterator;
typedef  boost::graph_traits<Graph>::edge_iterator g_edge_iterator;
typedef  boost::graph_traits<Graph>::in_edge_iterator in_edge_itr;

class graph_bfs_visitor : public boost::default_bfs_visitor
{
private:
   Marking search_marking;
   Graph G;
   nodes_markings_map n_markings_map;

public:
  graph_bfs_visitor(Marking m, Graph &g)
  {
      search_marking = m;
      G = g;
      n_markings_map = get(vertex_marking, G);;
  }

  // This is invoked when a vertex is encountered for the first time.
  template < typename Vertex, typename Graph >
  void discover_vertex(Vertex u, const Graph & g)
  {
    Q_UNUSED(g);
    Marking M = n_markings_map[u];

    // exception
    if(M == search_marking)
        throw u;
  }
};


class tree_bfs_visitor : public boost::default_bfs_visitor
{
  private:

	Marking M1;
	nodes_markings_map nodes;
	QList<g_node_descriptor>& m1_descriptors;

  public:

	tree_bfs_visitor(const Marking& M1, const nodes_markings_map& n_markings, 
		QList<g_node_descriptor>& list):m1_descriptors(list)
	{
	  this->M1 = M1;
	  nodes = n_markings;
	}

	// This is invoked when a vertex is encountered for the first time.
	template < typename Vertex, typename Graph >
	void discover_vertex(Vertex u, const Graph & g)
	{
	  Q_UNUSED(g);
	  Marking M = nodes[u];

	  if(M == M1)
	     m1_descriptors << u;
	}
};

#endif // BOOST_GRAPH_H 

