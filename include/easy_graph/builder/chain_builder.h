#ifndef HDF50E564_F050_476A_A479_F82B20F35C84
#define HDF50E564_F050_476A_A479_F82B20F35C84

#include "easy_graph/builder/link.h"
#include "easy_graph/graph/node_id.h"
#include "easy_graph/graph/node.h"

EG_NS_BEGIN

struct GraphBuilder;
struct Graph;

struct ChainBuilder {
	ChainBuilder(GraphBuilder& graphBuilder, EdgeType defaultEdgeType);

	struct LinkBuilder {

		using NodeObj = Node;

		LinkBuilder(ChainBuilder& chain, EdgeType defaultEdgeType);

		ChainBuilder& Node(const NodeObj& node);

		template<typename ...PARAMS>
		ChainBuilder& Node(const PARAMS&... params) {
			return this->Node(NodeObj(params...));
		}

		ChainBuilder& Ctrl(const std::string& label = "");
		ChainBuilder& Data(const std::string& label = "");
		ChainBuilder& Data(PortId srcId, PortId dstId, const std::string& label = "");

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
