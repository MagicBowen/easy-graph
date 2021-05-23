#include "graph.h"
#include "node.h"
#include "edge.h"
#include "node_visitor.h"
#include "edge_visitor.h"
#include "graph_layout.h"

EG_NS_BEGIN

Graph::Graph(const std::string& name)
: name(name) {
}

std::string Graph::getName() const {
	return name;
}

Node* Graph::addNode(const Node& node) {
	nodes.emplace(std::make_pair(node.getId(), node));
	return findNode(node.getId());
}

void Graph::addEdge(const Edge& edge) {
	edges.insert(edge);
}

Node* Graph::findNode(const NodeId& id) {
	auto it = nodes.find(id);
	if (it == nodes.end()) {
		return nullptr;
	}
	return &(it->second);
}

const Node* Graph::findNode(const NodeId& id) const {
	return const_cast<Graph&>(*this).findNode(id);
}

void Graph::accept(NodeVisitor& visitor) const {
	std::for_each(nodes.begin(), nodes.end(), [&visitor](auto& node){visitor.visit(node.second);});
}

void Graph::accept(EdgeVisitor& visitor) const {
	std::for_each(edges.begin(), edges.end(), [&visitor](auto edge){visitor.visit(edge);});
}

void Graph::layout(FlowDirection dir) const {
	GraphLayout::layout(*this, dir);
}

EG_NS_END
