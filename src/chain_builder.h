#ifndef HDF50E564_F050_476A_A479_F82B20F35C84
#define HDF50E564_F050_476A_A479_F82B20F35C84

#include "easy_graph/eg.h"
#include "edge_type.h"

EG_NS_BEGIN

struct Graph;
struct Node;
struct Edge;

struct ChainBuilder {
	ChainBuilder(Graph& graph, EdgeType type);

	struct ChainNodeBuilder {
		ChainNodeBuilder(ChainBuilder& chain, EdgeType edgeType);
		ChainBuilder& NODE(const Node& node);
	private:
		ChainBuilder& chain;
		EdgeType edgeType;
	} nodeFromEgde;

	ChainNodeBuilder* operator->();

private:
	ChainBuilder& addDstNodeOnEdge(const Node& node, EdgeType type);

private:
	Node* lastNode{nullptr};
	Graph& graph;
};

#define DATA_CHAIN(...) ChainBuilder(GR, DATA_EDGE) -> __VA_ARGS__
#define CTRL_CHAIN(...) ChainBuilder(GR, CTRL_EDGE) -> __VA_ARGS__

EG_NS_END

#endif
