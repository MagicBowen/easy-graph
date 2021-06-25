#include "easy_graph/checker/visitor/edge_check_visitor.h"
#include "easy_graph/graph/edge_type.h"

EG_NS_BEGIN

EdgeCheckVisitor::EdgeCheckVisitor(const Edge& edge)
: edge(edge) {
}

bool EdgeCheckVisitor::isTypeEqual(const EdgeType& type) const {
	return edge.getType() == type;
}

EG_NS_END
