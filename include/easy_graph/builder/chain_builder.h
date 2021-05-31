#ifndef HDF50E564_F050_476A_A479_F82B20F35C84
#define HDF50E564_F050_476A_A479_F82B20F35C84

#include "easy_graph/builder/link.h"
#include "easy_graph/graph/node_id.h"

EG_NS_BEGIN

struct GraphBuilder;
struct Graph;
struct Node;

struct ChainBuilder {
	ChainBuilder(GraphBuilder& graphBuilder, EdgeType defaultEdgeType);

	struct LinkBuilder {
		LinkBuilder(ChainBuilder& chain, EdgeType defaultEdgeType);

		ChainBuilder& NODE(const Node& node);

		template<typename ...GRAPHS>
		ChainBuilder& NODE(const NodeId& id, const GRAPHS&... graphs) {
			return this->NODE(Node(id, graphs...));
		}

		ChainBuilder& CTRL(const std::string& label = "");
		ChainBuilder& DATA(const std::string& label = "");
		ChainBuilder& DATA(PortId srcId, PortId dstId, const std::string& label = "");

	private:
		ChainBuilder& startLink(const Link& link);

	private:
		ChainBuilder& chain;
		EdgeType defaultEdgeType;
		Link fromLink;
	} linker;

	LinkBuilder* operator->();

private:
	ChainBuilder& linkTo(const Node&, const Link&);

private:
	Node* prevNode{nullptr};
	GraphBuilder& graphBuilder;
};

EG_NS_END

#endif
