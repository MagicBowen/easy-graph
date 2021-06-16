#include "easy_graph/builder/chain_builder.h"
#include "easy_graph/builder/graph_builder.h"

EG_NS_BEGIN

ChainBuilder::ChainBuilder(GraphBuilder& graphBuilder, const EdgeType& defaultEdgeType)
: graphBuilder(graphBuilder),
  linker(*this, defaultEdgeType) {
}

ChainBuilder::LinkBuilder* ChainBuilder::operator->() {
	return &linker;
}

const Node* ChainBuilder::findNode(const NodeId& id) const {
	return graphBuilder->findNode(id);
}

ChainBuilder::LinkBuilder::LinkBuilder(ChainBuilder& chain, const EdgeType& defaultEdgeType)
: chain(chain), defaultEdgeType(defaultEdgeType), fromLink(defaultEdgeType){
}

EG_NS_END
