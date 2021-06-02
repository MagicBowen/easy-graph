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

void Node::addSubgraph(const Graph& graph) {
	subgraphs.push_back(&graph);
}

void Node::accept(GraphVisitor& visitor) const {
	std::for_each(subgraphs.begin(), subgraphs.end(),  [&visitor](const auto& graph){visitor.visit(*graph);});
}

EG_NS_END
