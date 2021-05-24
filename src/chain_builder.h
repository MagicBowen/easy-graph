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
	ChainBuilder(GraphBuilder& graphBuilder, EdgeType defaultEdgeType);

	struct EdgeInfo {
		explicit EdgeInfo(EdgeType type) : type(type) {
			reset(type);
		}

		EdgeInfo(EdgeType type, const std::string& label, PortId srcPortId, PortId dstPortId)
		: type(type), label(label), srcPortId(srcPortId), dstPortId(dstPortId){
		}

		void reset(EdgeType type) {
			this->type = type;
			this->label = "";
			this->srcPortId = UNDEFINED_PORT_ID;
			this->dstPortId = UNDEFINED_PORT_ID;
		}

		EdgeType type;
		std::string label;
		PortId srcPortId;
		PortId dstPortId;
	};

	struct LinkBuilder {
		LinkBuilder(ChainBuilder& chain, EdgeType defaultEdgeType);

		ChainBuilder& NODE(const Node& node);
		ChainBuilder& CTRL(const std::string& label = "");
		ChainBuilder& DATA(const std::string& label = "");
		ChainBuilder& DATA(PortId srcId, PortId dstId, const std::string& label = "");

	private:
		ChainBuilder& addEdge(const EdgeInfo& edge);

	private:
		ChainBuilder& chain;
		EdgeType defaultEdgeType;
		EdgeInfo currentEdge;
	} linker;

	LinkBuilder* operator->();

private:
	ChainBuilder& addDstNodeOnEdge(const Node&, const EdgeInfo&);

private:
	Node* prevNode{nullptr};
	GraphBuilder& graphBuilder;
};

EG_NS_END

#endif
