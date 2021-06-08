#include "assertion/visitor/graph_assert_visitor.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/graph/endpoint.h"

EG_NS_BEGIN

bool GraphAssertVisitor::isEqualTo(const Graph& expect) const {
	if (!graph) return false;
	return (*graph) == expect;
}

bool GraphAssertVisitor::hasNode(const NodeId& id) const {
	if (!graph) return false;
	return graph->findNode(id) != nullptr;
}

template<typename PRED>
bool GraphAssertVisitor::isEdgeExisted(EdgeType type, PRED pred) const {
	if (!graph) return false;
	for (const auto& edge : edges) {
		if ((type == edge->getType()) && (pred(*edge))) {
			return true;
		}
	}
	return false;
}

bool GraphAssertVisitor::hasEdge(const NodeId& src, const NodeId& dst, EdgeType type) const {
	return isEdgeExisted(type, [&src, &dst](const Edge& edge) {
		return (src == edge.getSrc().getNodeId()) && (dst ==  edge.getDst().getNodeId());
	});
}

bool GraphAssertVisitor::hasEdge(const Endpoint& src, const Endpoint& dst, EdgeType type) const {
	return isEdgeExisted(type, [&src, &dst](const Edge& edge) {
		return (src == edge.getSrc()) && (dst ==  edge.getDst());
	});
}

Status GraphAssertVisitor::visit(const Graph& graph) {
	this->graph = &graph;
	this->name = this->graph->getName();
	return EG_SUCCESS;
}

Status GraphAssertVisitor::visit(const Node& node) {
	this->nodeCount++;
	return EG_SUCCESS;
}

Status GraphAssertVisitor::visit(const Edge& edge) {
	edges.push_back(&edge);
	this->edgeCount++;
	return EG_SUCCESS;
}

EG_NS_END
