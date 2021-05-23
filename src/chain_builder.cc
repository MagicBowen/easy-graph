#include "chain_builder.h"
#include "graph_builder.h"
#include "node.h"
#include "edge.h"

EG_NS_BEGIN

ChainBuilder::ChainBuilder(GraphBuilder& graphBuilder, EdgeType type)
: graphBuilder(graphBuilder),
  linker(*this, type) {
}

ChainBuilder::LinkBuilder* ChainBuilder::operator->() {
	return &linker;
}

ChainBuilder& ChainBuilder::addDstNodeOnEdge(const Node& node, EdgeType type, const std::string& label) {
	Node* currentNode = graphBuilder.addNode(node);
	if (prevNode) {
		graphBuilder.addEdge(type, label, *prevNode, *currentNode);
	}
	prevNode = currentNode;
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

ChainBuilder& ChainBuilder::LinkBuilder::addEdge(EdgeType edgeType, const std::string& label) {
	this->currentEdgeType = edgeType;
	this->currentEdgeLabel = label;
	return chain;
}

ChainBuilder& ChainBuilder::LinkBuilder::CTRL(const std::string& label) {
	return this->addEdge(CTRL_EDGE, label);
}

ChainBuilder& ChainBuilder::LinkBuilder::DATA(const std::string& label) {
	return this->addEdge(DATA_EDGE, label);
}

EG_NS_END
