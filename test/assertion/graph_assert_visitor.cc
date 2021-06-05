#include "assertion/graph_assert_visitor.h"
#include "easy_graph/graph/graph.h"

EG_NS_BEGIN

namespace {
	void setupNodeEdges(std::map<NodeId, Edges>& nodeEdges, const NodeId& id) {
		if (nodeEdges.find(id) == nodeEdges.end()) {
			nodeEdges[id] = Edges{};
		}
	}

	void classifyNodeEdge(std::map<NodeId, Edges>& nodeEdges, const NodeId& id, const Edge& edge) {
		auto item = nodeEdges.find(id);
		if(item != nodeEdges.end()) {
			nodeEdges[id].push_back(&edge);
		}
	}
}

bool GraphAssertVisitor::isEqualTo(const Graph&) const {
	return true;
}

bool GraphAssertVisitor::hasNode(const NodeId& id) const {
	if (!graph) return false;
	return graph->findNode(id) != nullptr;
}

bool GraphAssertVisitor::hasEdge(const NodeId& src, const NodeId& dst) const {
	if (!graph) return false;

	auto item = nodeEdges.find(src);
	if (item == nodeEdges.end()) {
		return false;
	}

	for(auto& e : item->second) {
		if (e->getDstNodeId() == dst) return true;
	}
	return false;
}

Status GraphAssertVisitor::visit(const Graph& graph) {
	this->graph = &graph;
	this->name = this->graph->getName();
	return EG_SUCCESS;
}

Status GraphAssertVisitor::visit(const Node& node) {
	setupNodeEdges(nodeEdges, node.getId());
	this->nodeCount++;
	return EG_SUCCESS;
}

Status GraphAssertVisitor::visit(const Edge& edge) {
	classifyNodeEdge(nodeEdges, edge.getSrcNodeId(), edge);
	this->edgeCount++;
	return EG_SUCCESS;
}

EG_NS_END
