#include "easy_graph/graph/graph.h"
#include "easy_graph/graph/graph_visitor.h"
#include "easy_graph/layout/graph_layout.h"

EG_NS_BEGIN

namespace {
	bool isAllNodesEqual(const std::map<NodeId, Node>& nodes, const Graph& graph) {
		for (const auto& ln : nodes) {
			auto rn = graph.findNode(ln.first);
			if (!rn) return false;
			if (ln.second != *rn) return false;
		}
		return true;
	}

	bool isAllEdgesEqual(const std::set<Edge>& edges, const Graph& graph) {
		for (const auto& le : edges) {
			if (!graph.findEdge(le)) return false;
		}
		return true;
	}
}

Graph::Graph(const std::string& name)
: name(name) {
}

__DEF_EQUALS(Graph) {
	if (nodes.size() != rhs.nodes.size()) return false;
	if (edges.size() != rhs.edges.size()) return false;

	if (!isAllNodesEqual(nodes, rhs)) return false;
	if (!isAllEdgesEqual(edges, rhs)) return false;
	return true;
}

std::string Graph::getName() const {
	return name;
}

Node* Graph::findNode(const NodeId& id) {
	auto it = nodes.find(id);
	if (it == nodes.end()) return nullptr;
	return &(it->second);
}

const Node* Graph::findNode(const NodeId& id) const {
	return const_cast<Graph&>(*this).findNode(id);
}

Edge* Graph::findEdge(const Edge& edge) {
	auto result = edges.find(edge);
	if (result == edges.end()) return nullptr;
	return &(const_cast<Edge&>(*result));
}

const Edge* Graph::findEdge(const Edge& edge) const {
	return const_cast<Graph&>(*this).findEdge(edge);
}

std::pair<const Node*, const Node*> Graph::findNodesOn(const Edge& edge) const {
	return std::make_pair(findNode(edge.getSrc().getNodeId()), findNode(edge.getDst().getNodeId()));
}

std::pair<Node*, Node*> Graph::findNodesOn(const Edge& edge) {
	return const_cast<Graph&>(*this).findNodesOn(edge);
}

void Graph::remove(const NodeId& id) {
	nodes.erase(id);
}

void Graph::remove(const Edge& edge) {
	edges.erase(edge);
}

void Graph::accept(GraphVisitor& visitor) const {
	visitor.visit(*this);
	std::for_each(nodes.cbegin(), nodes.cend(), [&visitor](const auto& node){visitor.visit(node.second);});
	std::for_each(edges.cbegin(), edges.cend(), [&visitor](const auto& edge){visitor.visit(edge);});
}

Status Graph::layout(const LayoutOption* option) const {
	return GraphLayout::getInstance().layout(*this, option);
}

EG_NS_END
