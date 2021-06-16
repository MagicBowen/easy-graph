#ifndef HDF50E564_F050_476A_A479_F82B20F35C84
#define HDF50E564_F050_476A_A479_F82B20F35C84

#include "easy_graph/builder/link.h"
#include "easy_graph/builder/link_builder.h"
#include "easy_graph/builder/edge_builder.h"
#include "easy_graph/builder/node_builder.h"
#include "easy_graph/builder/graph_builder.h"
#include "easy_graph/infra/ext_traits.h"

EG_NS_BEGIN

struct Graph;
struct Edge;

struct ChainBuilder {
	ChainBuilder(GraphBuilder& graphBuilder, const EdgeType& defaultEdgeType);

	struct LinkBuilder {

		using NodeObj = Node;
		using EdgeObj = Edge;

		LinkBuilder(ChainBuilder& chain, const EdgeType& defaultEdgeType);

		template<typename NODE, IS_SAME_CONCEPT(NODE, Node)>
		ChainBuilder& Node(NODE && node) {
			chain.linkTo(std::forward<NODE>(node), fromLink);
			return chain;
		}

		template<typename ...PARAMS>
		ChainBuilder& Node(const NodeId& id, PARAMS &&... params) {
			auto node = chain.findNode(id);
			if (node) {
				return this->Node(*node);
			}
			return this->Node(std::move(node_of(id, std::forward<PARAMS>(params)...)));
		}

		template<typename ...PARAMS>
		ChainBuilder& Edge(PARAMS && ...params) {
			fromLink = std::move(link_of(defaultEdgeType, std::forward<PARAMS>(params)...));
			return chain;
		}

		template<typename ...TS>
		ChainBuilder& Ctrl(TS && ...ts) {
			return this->Edge(ctrl_edge(), std::forward<TS>(ts)...);
		}

		template<typename ...TS>
		ChainBuilder& Data(TS && ...ts) {
			return this->Edge(data_edge(), std::forward<TS>(ts)...);
		}

	private:
		ChainBuilder& chain;
		const EdgeType& defaultEdgeType;
		Link fromLink;
	} linker;

	LinkBuilder* operator->();

private:
	template<typename NODE>
	ChainBuilder& linkTo(NODE && node, Link& link) {
		Node* currentNode = graphBuilder.buildNode(std::forward<NODE>(node));
		if (prevNode) {
			graphBuilder.buildEdge(*prevNode, *currentNode, link);
		}
		prevNode = currentNode;
		return *this;
	}

	const Node* findNode(const NodeId&) const;

private:
	Node* prevNode{nullptr};
	GraphBuilder& graphBuilder;
};

EG_NS_END

#endif
