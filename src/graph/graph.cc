#include "easy_graph/graph/graph.h"
#include "easy_graph/graph/graph_visitor.h"
#include "easy_graph/layout/graph_layout.h"

EG_NS_BEGIN

Graph::Graph(const std::string& name)
: name(name) {
}

std::string Graph::getName() const {
	return name;
}

Node* Graph::addNode(const Node& node) {
	auto result = nodes.emplace(node.getId(), node);
	return &(result.first->second);
}

Edge* Graph::addEdge(const Edge& edge) {
	auto result = edges.emplace(edge);
	return &(const_cast<Edge&>(*(result.first)));
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

std::pair<const Node*, const Node*> Graph::findNodePair(const Edge& edge) const {
	return std::make_pair(findNode(edge.getSrc().getNodeId()), findNode(edge.getDst().getNodeId()));
}

std::pair<Node*, Node*> Graph::findNodePair(const Edge& edge) {
	return std::make_pair(findNode(edge.getSrc().getNodeId()), findNode(edge.getDst().getNodeId()));
}

void Graph::accept(GraphVisitor& visitor) const {
	visitor.visit(*this);
	std::for_each(nodes.begin(), nodes.end(), [&visitor](const auto& node){visitor.visit(node.second);});
	std::for_each(edges.begin(), edges.end(), [&visitor](const auto& edge){visitor.visit(edge);});
}

Status Graph::layout(const LayoutOption* option) const {
	return GraphLayout::getInstance().layout(*this, option);
}

EG_NS_END
