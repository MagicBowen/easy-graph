#ifndef HDF50E564_F050_476A_A479_F82B20F35C84
#define HDF50E564_F050_476A_A479_F82B20F35C84

#include "edge_type.h"
#include "port_id.h"
#include <string>

EG_NS_BEGIN

struct GraphBuilder;
struct Node;
struct Edge;

struct ChainBuilder {
	ChainBuilder(GraphBuilder& graphBuilder, EdgeType type);

	struct LinkBuilder {
		LinkBuilder(ChainBuilder& chain, EdgeType edgeType);

		ChainBuilder& NODE(const Node& node);
		ChainBuilder& CTRL(const std::string& label = "");
		ChainBuilder& DATA(const std::string& label = "");
		ChainBuilder& DATA(PortId srcId, PortId dstId, const std::string& label = "");

	private:
		ChainBuilder& addEdge(EdgeType edgeType,
				              const std::string& label,
							  PortId srcPort,
							  PortId dstPort);
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
	GraphBuilder& graphBuilder;
};

EG_NS_END

#endif
