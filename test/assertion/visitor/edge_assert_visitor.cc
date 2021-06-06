#include "assertion/visitor/edge_assert_visitor.h"
#include "easy_graph/graph/edge.h"
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
	return edges[0]->getType() == EdgeType::CTRL;
}

bool EdgeAssertVisitor::isDataType(const PortId& src, const PortId& dst) const {
	auto edge = findEdge(src, dst);
	if (!edge) return false;

	return edge->getType() == EdgeType::DATA;
}

const Edge* EdgeAssertVisitor::findEdge(const PortId& src, const PortId& dst) const {
	for (const auto& e : edges) {
		if ((e->getSrc().getPortId() == src) && (e->getDst().getPortId() == dst)) {
			return e;
		}
	}
	return nullptr;
}

Status EdgeAssertVisitor::visit(const Edge& edge) {
	if ((edge.getSrc().getNodeId() == srcNode.getId()) &&
		(edge.getDst().getNodeId() == dstNode.getId())) {
		edges.push_back(&edge);
		count++;
	}
	return EG_SUCCESS;
}

EG_NS_END