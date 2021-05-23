#ifndef HDF50E564_F050_476A_A479_F82B20F35C84
#define HDF50E564_F050_476A_A479_F82B20F35C84

#include "easy_graph/eg.h"
#include "edge_type.h"
#include <string>

EG_NS_BEGIN

struct Graph;
struct Node;
struct Edge;

struct ChainBuilder {
	ChainBuilder(Graph& graph, EdgeType type);

	struct LinkBuilder {
		LinkBuilder(ChainBuilder& chain, EdgeType edgeType);
		ChainBuilder& NODE(const Node& node);
		ChainBuilder& EDGE(EdgeType edgeType = DATA_EDGE, const std::string& label = "");
		ChainBuilder& C_EDGE(const std::string& label = "");
		ChainBuilder& D_EDGE(const std::string& label = "");
	private:
		ChainBuilder& chain;
		EdgeType defaultEdgeType;
		EdgeType currentEdgeType;
		std::string currentEdgeLabel;
	} linker;

	LinkBuilder* operator->();

private:
	ChainBuilder& addDstNodeOnEdge(const Node&, EdgeType, const std::string&);

private:
	Node* prevNode{nullptr};
	Graph& graph;
};


#define DATA_CHAIN(...) ::EG_NS::ChainBuilder(GR, DATA_EDGE) -> __VA_ARGS__
#define CTRL_CHAIN(...) ::EG_NS::ChainBuilder(GR, CTRL_EDGE) -> __VA_ARGS__
#define CHAIN(...) DATA_CHAIN(__VA_ARGS__)

EG_NS_END

#endif
