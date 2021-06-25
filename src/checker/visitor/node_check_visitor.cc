#include "easy_graph/checker/visitor/node_check_visitor.h"
#include "easy_graph/graph/subgraph_visitor.h"
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

	struct NodeSubgraphVisitor : SubgraphVisitor {
		NodeSubgraphVisitor(std::vector<std::string>& subgraphs)
		: subgraphs(subgraphs) {
		}

	private:
		void visit(const Subgraph& graph) override {
			subgraphs.push_back(graph.getName());
		}

	private:
		std::vector<std::string>& subgraphs;
	};
}

NodeCheckVisitor::NodeCheckVisitor(const Node& node)
: node(node){
	NodeSubgraphVisitor visitor(subgraphs);
	node.accept(visitor);
	subgraphCount = subgraphs.size();

}

bool NodeCheckVisitor::prevNextTo(const NodeId& id) const {
	return findEdgeBy(postEdges, [id](const Edge& edge) {
		return edge.getDst().getNodeId() == id;
	});
}

bool NodeCheckVisitor::postNextTo(const NodeId& id) const {
	return findEdgeBy(prevEdges, [id](const Edge& edge) {
		return edge.getSrc().getNodeId() == id;
	});
}

bool NodeCheckVisitor::prevNextTo(const Endpoint& dst) const {
	return findEdgeBy(postEdges, [dst](const Edge& edge) {
		return edge.getDst() == dst;
	});
}

bool NodeCheckVisitor::postNextTo(const Endpoint& src) const {
	return findEdgeBy(prevEdges, [src](const Edge& edge) {
		return edge.getSrc() == src;
	});
}

bool NodeCheckVisitor::isSource() const {
	return (inputCount == 0) && (outputCount > 0);
}

bool NodeCheckVisitor::isSink() const {
	return (inputCount > 0) && (outputCount == 0);
}

bool NodeCheckVisitor::isIsolated() const {
	return (inputCount == 0) && (outputCount == 0);
}

bool NodeCheckVisitor::hasSubgraph(const std::string& name) const {
	for (const auto& s : subgraphs) {
		if (s == name) return true;
	}
	return false;
}

void NodeCheckVisitor::visit(const Edge& edge) {
	if (edge.getSrc().getNodeId() == node.getId()) {
		postEdges.push_back(&edge);
		outputCount++;
	}
	if (edge.getDst().getNodeId() == node.getId()) {
		prevEdges.push_back(&edge);
		inputCount++;
	}
}

EG_NS_END
