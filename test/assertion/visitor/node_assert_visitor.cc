#include "assertion/visitor/node_assert_visitor.h"
#include "easy_graph/graph/edge.h"
#include "easy_graph/graph/node.h"

EG_NS_BEGIN

namespace {
	template<typename PRED>
	bool findEdgeBy(const Edges& edges, PRED pred) {
		for (const auto& edge : edges) {
			if (pred(*edge)) return true;
		}
		return false;
	}
}

NodeAssertVisitor::NodeAssertVisitor(const Node& node)
: node(node){
}

bool NodeAssertVisitor::prevNextTo(const NodeId& id) const {
	return findEdgeBy(postEdges, [id](const Edge& edge) {
		return edge.getDstEndpoint().node == id;
	});
}

bool NodeAssertVisitor::postNextTo(const NodeId& id) const {
	return findEdgeBy(prevEdges, [id](const Edge& edge) {
		return edge.getSrcEndpoint().node == id;
	});
}

bool NodeAssertVisitor::prevNextTo(const Endpoint& dst) const {
	return findEdgeBy(postEdges, [dst](const Edge& edge) {
		return edge.getDstEndpoint() == dst;
	});
}

bool NodeAssertVisitor::postNextTo(const Endpoint& src) const {
	return findEdgeBy(prevEdges, [src](const Edge& edge) {
		return edge.getSrcEndpoint() == src;
	});
}

bool NodeAssertVisitor::isSource() const {
	return (inputCount == 0) && (outputCount > 0);
}

bool NodeAssertVisitor::isSink() const {
	return (inputCount > 0) && (outputCount == 0);
}

bool NodeAssertVisitor::isIsolated() const {
	return (inputCount == 0) && (outputCount == 0);
}

Status NodeAssertVisitor::visit(const Edge& edge) {
	if (edge.getSrcEndpoint().node == node.getId()) {
		postEdges.push_back(&edge);
		outputCount++;
	}
	if (edge.getDstEndpoint().node == node.getId()) {
		prevEdges.push_back(&edge);
		inputCount++;
	}
	return EG_SUCCESS;
}

EG_NS_END
