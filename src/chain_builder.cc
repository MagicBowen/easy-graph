#include "chain_builder.h"
#include "node.h"
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
		graph.addEdge(Edge(type, label, NodePort(*prevNode, 0), NodePort(*current_node, 0)));
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
