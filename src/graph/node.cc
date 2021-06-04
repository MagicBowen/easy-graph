#include "easy_graph/graph/node.h"
#include "easy_graph/graph/graph_visitor.h"

EG_NS_BEGIN

__DEF_EQUALS(Node)
{
	return id == rhs.id;
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
