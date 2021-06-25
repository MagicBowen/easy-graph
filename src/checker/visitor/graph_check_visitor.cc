#include "easy_graph/checker/visitor/graph_check_visitor.h"
#include "easy_graph/graph/graph.h"

EG_NS_BEGIN

bool GraphCheckVisitor::isEqualTo(const Graph& expect) const {
	if (!graph) return false;
	return (*graph) == expect;
}

bool GraphCheckVisitor::hasNode(const NodeId& id) const {
	if (!graph) return false;
	return graph->findNode(id) != nullptr;
}

bool GraphCheckVisitor::hasEdge(const Edge& edge) const {
	return graph->findEdge(edge) != nullptr;
}

void GraphCheckVisitor::dump() const {
	if (graph) graph->layout();
}

void GraphCheckVisitor::visit(const Graph& graph) {
	this->graph = &graph;
	this->name = this->graph->getName();
}

void GraphCheckVisitor::visit(const Node& node) {
	this->nodeCount++;
}

void GraphCheckVisitor::visit(const Edge& edge) {
	this->edgeCount++;
}

EG_NS_END
