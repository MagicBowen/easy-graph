#include "chain_builder.h"
#include "graph_builder.h"
#include "node.h"
#include "edge.h"

EG_NS_BEGIN

ChainBuilder::ChainBuilder(GraphBuilder& graphBuilder, EdgeType defaultEdgeType)
: graphBuilder(graphBuilder),
  linker(*this, defaultEdgeType) {
}

ChainBuilder::LinkBuilder* ChainBuilder::operator->() {
	return &linker;
}

ChainBuilder& ChainBuilder::addDstNodeOnEdge(const Node& node, const EdgeInfo& edge) {
	Node* currentNode = graphBuilder.addNode(node);
	if (prevNode) {
		graphBuilder.addEdge(edge.type, edge.label, *prevNode, *currentNode);
	}
	prevNode = currentNode;
	return *this;
}

ChainBuilder::LinkBuilder::LinkBuilder(ChainBuilder& chain, EdgeType defaultEdgeType)
: chain(chain), defaultEdgeType(defaultEdgeType), currentEdge(defaultEdgeType){
}

ChainBuilder& ChainBuilder::LinkBuilder::NODE(const Node& node) {
	chain.addDstNodeOnEdge(node, currentEdge);
	this->currentEdge.reset(defaultEdgeType);
	return chain;
}

ChainBuilder& ChainBuilder::LinkBuilder::addEdge(const EdgeInfo& edge) {
	this->currentEdge = edge;
	return chain;
}

ChainBuilder& ChainBuilder::LinkBuilder::CTRL(const std::string& label) {
	return this->addEdge(EdgeInfo(CTRL_EDGE, label, UNDEFINED_PORT_ID, UNDEFINED_PORT_ID));
}

ChainBuilder& ChainBuilder::LinkBuilder::DATA(const std::string& label) {
	return this->addEdge(EdgeInfo(DATA_EDGE, label, UNDEFINED_PORT_ID, UNDEFINED_PORT_ID));
}

ChainBuilder& ChainBuilder::LinkBuilder::DATA(PortId srcPort, PortId dstPort, const std::string& label) {
	return this->addEdge(EdgeInfo(DATA_EDGE, label, srcPort, dstPort));
}

EG_NS_END
