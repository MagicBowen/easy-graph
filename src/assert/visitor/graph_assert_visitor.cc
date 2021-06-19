#include "easy_graph/assert/visitor/graph_assert_visitor.h"
#include "easy_graph/graph/graph.h"

EG_NS_BEGIN

bool GraphAssertVisitor::isEqualTo(const Graph& expect) const {
	if (!graph) return false;
	return (*graph) == expect;
}

bool GraphAssertVisitor::hasNode(const NodeId& id) const {
	if (!graph) return false;
	return graph->findNode(id) != nullptr;
}

bool GraphAssertVisitor::hasEdge(const Edge& edge) const {
	return graph->findEdge(edge) != nullptr;
}

void GraphAssertVisitor::dump() const {
	if (graph) graph->layout();
}

void GraphAssertVisitor::visit(const Graph& graph) {
	this->graph = &graph;
	this->name = this->graph->getName();
}

void GraphAssertVisitor::visit(const Node& node) {
	this->nodeCount++;
}

void GraphAssertVisitor::visit(const Edge& edge) {
	this->edgeCount++;
}

EG_NS_END
