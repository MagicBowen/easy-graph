#include "easy_graph/graph/node.h"
#include "easy_graph/graph/subgraph_visitor.h"
#include "easy_graph/infra/vector_eq.h"

EG_NS_BEGIN

namespace {
	bool isSubgraphsEqual(const std::vector<Subgraph>& lhs, const std::vector<Subgraph>& rhs) {
		return is_vector_unorder_equal(lhs, rhs);
	}
}

Node::Node(const NodeId& id) : id(id) {
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

void Node::accept(SubgraphVisitor& visitor) const {
	std::for_each(subgraphs.cbegin(), subgraphs.cend(),  [&visitor](const auto& subgraph){visitor.visit(subgraph);});
}

EG_NS_END
