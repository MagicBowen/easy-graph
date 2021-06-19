#include "easy_graph/assert/visitor/edge_assert_visitor.h"
#include "easy_graph/graph/edge_type.h"

EG_NS_BEGIN

EdgeAssertVisitor::EdgeAssertVisitor(const Edge& edge)
: edge(edge) {
}

bool EdgeAssertVisitor::isTypeEqual(const EdgeType& type) const {
	return edge.getType() == type;
}

EG_NS_END
