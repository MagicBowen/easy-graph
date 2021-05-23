#include "chain_builder.h"
#include "graph.h"
#include "edge.h"

EG_NS_BEGIN

ChainBuilder::ChainBuilder(Graph& graph, EdgeType type)
: graph(graph),
  linker(*this, type) {
}

ChainBuilder::LinkBuilder* ChainBuilder::operator->() {
	return &linker;
}

ChainBuilder& ChainBuilder::addDstNodeOnEdge(const Node& node, EdgeType type, const std::string& label) {
	Node* current_node = graph.addNode(node);
	if (prevNode) {
		graph.addEdge(Edge(type, label, *prevNode, *current_node));
	}
	prevNode = current_node;
	return *this;
}

ChainBuilder::LinkBuilder::LinkBuilder(ChainBuilder& chain, EdgeType edgeType)
: chain(chain), defaultEdgeType(edgeType), currentEdgeType(edgeType) {
}

ChainBuilder& ChainBuilder::LinkBuilder::NODE(const Node& node) {
	chain.addDstNodeOnEdge(node, currentEdgeType, currentEdgeLabel);
	this->currentEdgeType = defaultEdgeType;
	this->currentEdgeLabel = "";
	return chain;
}

ChainBuilder& ChainBuilder::LinkBuilder::EDGE(EdgeType edgeType, const std::string& label) {
	this->currentEdgeType = edgeType;
	this->currentEdgeLabel = label;
	return chain;
}

ChainBuilder& ChainBuilder::LinkBuilder::C_EDGE(const std::string& label) {
	return this->EDGE(CTRL_EDGE, label);
}

ChainBuilder& ChainBuilder::LinkBuilder::D_EDGE(const std::string& label) {
	return this->EDGE(DATA_EDGE, label);
}

EG_NS_END
