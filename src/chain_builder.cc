#include "chain_builder.h"
#include "graph_builder.h"

EG_NS_BEGIN

ChainBuilder::ChainBuilder(GraphBuilder& graphBuilder, EdgeType defaultEdgeType)
: graphBuilder(graphBuilder),
  linker(*this, defaultEdgeType) {
}

ChainBuilder::LinkBuilder* ChainBuilder::operator->() {
	return &linker;
}

ChainBuilder& ChainBuilder::linkTo(const Node& node, const Link& link) {
	Node* currentNode = graphBuilder.buildNode(node);
	if (prevNode) {
		graphBuilder.buildEdge(*prevNode, *currentNode, link);
	}
	prevNode = currentNode;
	return *this;
}

ChainBuilder::LinkBuilder::LinkBuilder(ChainBuilder& chain, EdgeType defaultEdgeType)
: chain(chain), defaultEdgeType(defaultEdgeType), fromLink(defaultEdgeType){
}

ChainBuilder& ChainBuilder::LinkBuilder::NODE(const Node& node) {
	chain.linkTo(node, fromLink);
	fromLink.reset(defaultEdgeType);
	return chain;
}

ChainBuilder& ChainBuilder::LinkBuilder::startLink(const Link& link) {
	this->fromLink = link;
	return chain;
}

ChainBuilder& ChainBuilder::LinkBuilder::CTRL(const std::string& label) {
	return this->startLink(Link(CTRL_EDGE, label, UNDEFINED_PORT_ID, UNDEFINED_PORT_ID));
}

ChainBuilder& ChainBuilder::LinkBuilder::DATA(const std::string& label) {
	return this->startLink(Link(DATA_EDGE, label, UNDEFINED_PORT_ID, UNDEFINED_PORT_ID));
}

ChainBuilder& ChainBuilder::LinkBuilder::DATA(PortId srcPort, PortId dstPort, const std::string& label) {
	return this->startLink(Link(DATA_EDGE, label, srcPort, dstPort));
}

EG_NS_END
