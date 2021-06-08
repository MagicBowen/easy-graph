#include "easy_graph/graph/node.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/graph/graph_visitor.h"

EG_NS_BEGIN

namespace {
	bool isSubgraphsEqual(const std::vector<const Graph*>& lhs, const std::vector<const Graph*>& rhs) {
		if (lhs.size() != rhs.size()) return false;
		for (auto lg : lhs) {
			auto result = std::find_if(rhs.begin(), rhs.end(), [&lg](const auto& rg) {
				return (*lg) == (*rg);
			});
			if (result == rhs.end()) return false;
		}
		return true;
	}
}

__DEF_EQUALS(Node)
{
	if (id != rhs.id) return false;
	return isSubgraphsEqual(subgraphs, rhs.subgraphs);
}

__DEF_COMP(Node)
{
	return id < rhs.id;
}

NodeId Node::getId() const {
	return id;
}

Node& Node::packing(const BoxPtr& box) {
	this->box = box;
	return *this;
}

Node& Node::addSubgraph(const Graph& graph) {
	subgraphs.push_back(&graph);
	return *this;
}

void Node::accept(GraphVisitor& visitor) const {
	std::for_each(subgraphs.begin(), subgraphs.end(),  [&visitor](const auto& graph){visitor.visit(*graph);});
}

EG_NS_END
