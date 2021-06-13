#ifndef HDF50E564_F050_476A_A479_F82B20F35C84
#define HDF50E564_F050_476A_A479_F82B20F35C84

#include "easy_graph/builder/link.h"
#include "easy_graph/builder/link_builder.h"
#include "easy_graph/builder/node_builder.h"
#include "easy_graph/builder/edge_types/ctrl_edge_type.h"
#include "easy_graph/builder/edge_types/data_edge_type.h"

EG_NS_BEGIN

struct GraphBuilder;
struct Graph;
struct Edge;

struct ChainBuilder {
	ChainBuilder(GraphBuilder& graphBuilder, const EdgeType& defaultEdgeType);

	struct LinkBuilder {

		using NodeObj = Node;
		using EdgeObj = Edge;

		LinkBuilder(ChainBuilder& chain, const EdgeType& defaultEdgeType);

		ChainBuilder& Node(const NodeObj& node);

		template<typename ...PARAMS>
		ChainBuilder& Node(const NodeId& id, PARAMS &&... params) {
			auto node = chain.findNode(id);
			if (node) {
				return this->Node(*node);
			}
			return this->Node(makeNode(id, std::forward<PARAMS>(params)...));
		}

		template<typename ...PARAMS>
		ChainBuilder& Edge(PARAMS && ...params) {
			makeLink(this->fromLink, std::forward<PARAMS>(params)...);
			return chain;
		}

		template<typename ...TS>
		ChainBuilder& Ctrl(TS && ...ts) {
			return this->Edge(EDGE_CTRL, std::forward<TS>(ts)...);
		}

		template<typename ...TS>
		ChainBuilder& Data(TS && ...ts) {
			return this->Edge(EDGE_DATA, std::forward<TS>(ts)...);
		}

	private:
		ChainBuilder& chain;
		const EdgeType& defaultEdgeType;
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
