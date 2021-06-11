#include "easy_graph/builder/chain_builder.h"
#include "easy_graph/builder/graph_builder.h"

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

const Node* ChainBuilder::findNode(const NodeId& id) const {
	return graphBuilder->findNode(id);
}

ChainBuilder::LinkBuilder::LinkBuilder(ChainBuilder& chain, EdgeType defaultEdgeType)
: chain(chain), defaultEdgeType(defaultEdgeType), fromLink(defaultEdgeType){
}

ChainBuilder& ChainBuilder::LinkBuilder::Node(const NodeObj& node) {
	chain.linkTo(node, fromLink);
	fromLink.reset(defaultEdgeType);
	return chain;
}

EG_NS_END
