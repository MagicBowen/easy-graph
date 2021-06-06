#ifndef HDF50E564_F050_476A_A479_F82B20F35C84
#define HDF50E564_F050_476A_A479_F82B20F35C84

#include "easy_graph/builder/link.h"
#include "easy_graph/graph/node_id.h"
#include "easy_graph/graph/node.h"

EG_NS_BEGIN

struct GraphBuilder;
struct Graph;
struct Edge;

struct ChainBuilder {
	ChainBuilder(GraphBuilder& graphBuilder, EdgeType defaultEdgeType);

	struct LinkBuilder {

		using NodeObj = Node;
		using EdgeObj = Edge;

		LinkBuilder(ChainBuilder& chain, EdgeType defaultEdgeType);

		ChainBuilder& Node(const NodeObj& node);

		template<typename ...PARAMS>
		ChainBuilder& Node(const NodeId& id, const PARAMS&... params) {
			auto node = chain.findNode(id);
			if (node) {
				return this->Node(*node);
			}
			return this->Node(NodeObj(id, params...));
		}

		ChainBuilder& Ctrl(const std::string& label = "");
		ChainBuilder& Data(const std::string& label = "");

		ChainBuilder& Data(PortId srcId = UNDEFINED_PORT_ID,
						   PortId dstId = UNDEFINED_PORT_ID,
						   const std::string& label = "");

		ChainBuilder& Edge(EdgeType type,
				           PortId srcId = UNDEFINED_PORT_ID,
						   PortId dstId = UNDEFINED_PORT_ID,
						   const std::string& label = "");

	private:
		ChainBuilder& startLink(const Link&);

	private:
		ChainBuilder& chain;
		EdgeType defaultEdgeType;
		Link fromLink;
	} linker;

	LinkBuilder* operator->();

private:
	ChainBuilder& linkTo(const Node&, const Link&);
	const Node* findNode(const NodeId&) const;

private:
	Node* prevNode{nullptr};
	GraphBuilder& graphBuilder;
};

EG_NS_END

#endif
