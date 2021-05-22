#include "graph.h"
#include "node.h"
#include "edge.h"
#include "node_visitor.h"
#include "edge_visitor.h"

EG_NS_BEGIN

Graph::Graph(const std::string name)
: name(name) {
}

void Graph::addNode(const Node& node) {
	nodes.insert(node);
}

void Graph::addEdge(const Edge& edge) {
	edges.insert(edge);
}

void Graph::accept(NodeVisitor& visitor) const {
	std::for_each(nodes.begin(), nodes.end(), [&visitor](auto node){visitor.visit(node);});
}

void Graph::accept(EdgeVisitor& visitor) const {
	std::for_each(edges.begin(), edges.end(), [&visitor](auto edge){visitor.visit(edge);});
}

EG_NS_END
