#include "assertion/visitor/edge_assert_visitor.h"
#include "easy_graph/builder/edge_type/ctrl_edge_type.h"
#include "easy_graph/builder/edge_type/data_edge_type.h"
#include "easy_graph/graph/node.h"

EG_NS_BEGIN

EdgeAssertVisitor::EdgeAssertVisitor(const Node& src, const Node& dst)
: srcNode(src), dstNode(dst) {
}

bool EdgeAssertVisitor::linked(const PortId& src, const PortId& dst) const {
	return (findEdge(src, dst) != nullptr);
}

bool EdgeAssertVisitor::isCtrlType() const {
	if (count != 1) return false;
	return edges[0]->getType() == CTRL_EDGE;
}

bool EdgeAssertVisitor::isDataType(const PortId& src, const PortId& dst) const {
	auto edge = findEdge(src, dst);
	if (!edge) return false;

	return edge->getType() == DATA_EDGE;
}

const Edge* EdgeAssertVisitor::findEdge(const PortId& src, const PortId& dst) const {
	for (const auto& e : edges) {
		if ((e->getSrc().getPortId() == src) && (e->getDst().getPortId() == dst)) {
			return e;
		}
	}
	return nullptr;
}

void EdgeAssertVisitor::visit(const Edge& edge) {
	if ((edge.getSrc().getNodeId() == srcNode.getId()) &&
		(edge.getDst().getNodeId() == dstNode.getId())) {
		edges.push_back(&edge);
		count++;
	}
}

EG_NS_END
