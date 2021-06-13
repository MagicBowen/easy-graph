#ifndef HDF50E564_F050_476A_A479_F82B20F35C84
#define HDF50E564_F050_476A_A479_F82B20F35C84

#include "easy_graph/builder/link.h"
#include "easy_graph/graph/node_id.h"
#include "easy_graph/graph/node.h"
#include "easy_graph/infra/ext_traits.h"

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
			return this->Node(NodeObj(id, std::forward<PARAMS>(params)...));
		}

		template<typename T, typename ...TS>
		ChainBuilder& Edge(T && t, TS && ...ts) {
			if constexpr (std::is_same_v<EdgeType, std::decay_t<T>>) {
				this->fromLink.type = &t;
			} else if constexpr (std::is_convertible_v<std::decay_t<T>, PortId>) {
				this->fromLink.setPortId(t);
			} else if constexpr (std::is_same_v<Attribute, std::decay_t<T>>) {
				this->fromLink.attrs.set(std::forward<T>(t));
			} else if constexpr (std::is_same_v<Attributes, std::decay_t<T>>) {
				this->fromLink.attrs.merge(std::forward<T>(t));
			} else {
				static_assert(!sizeof(T), "Unsupported edge construction type!");
			}
			return this->Edge(std::forward<TS>(ts)...);
		}
		template<typename ...TS>
		ChainBuilder& Ctrl(TS && ...ts) {
			return this->Edge(EdgeType::CTRL(), std::forward<TS>(ts)...);
		}
		template<typename ...TS>
		ChainBuilder& Data(TS && ...ts) {
			return this->Edge(EdgeType::DATA(), std::forward<TS>(ts)...);
		}

	private:
		ChainBuilder& Edge() {
			return chain;
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
