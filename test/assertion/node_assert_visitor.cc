#include "assertion/node_assert_visitor.h"

EG_NS_BEGIN

NodeAssertVisitor::NodeAssertVisitor(const Node& node)
: node(node){
}

bool NodeAssertVisitor::prevNextTo(const NodeId& id) const {
	return false;
}

bool NodeAssertVisitor::postNextTo(const NodeId& id) const {
	return false;
}

Status NodeAssertVisitor::visit(const Graph& graph) {
	return EG_SUCCESS;
}

Status NodeAssertVisitor::visit(const Node& node) {
	return EG_SUCCESS;
}

Status NodeAssertVisitor::visit(const Edge& edge) {
	return EG_SUCCESS;
}

EG_NS_END
