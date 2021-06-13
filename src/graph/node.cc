#include "easy_graph/graph/node.h"
#include "easy_graph/graph/subgraph_visitor.h"

EG_NS_BEGIN

namespace {
	bool isSubgraphsEqual(const std::vector<Subgraph>& lhs, const std::vector<Subgraph>& rhs) {
		if (lhs.size() != rhs.size()) return false;
		for (auto lg : lhs) {
			auto result = std::find_if(rhs.begin(), rhs.end(), [&lg](const auto& rg) {
				return lg == rg;
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

Node& Node::addSubgraph(const Subgraph& graph) {
	subgraphs.push_back(graph);
	return *this;
}

bool Node::hasSubgraph() const {
	return subgraphs.size() != 0;
}

void Node::accept(SubgraphVisitor& visitor) const {
	std::for_each(subgraphs.begin(), subgraphs.end(),  [&visitor](const auto& subgraph){visitor.visit(subgraph);});
}

EG_NS_END
