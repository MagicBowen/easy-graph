#ifndef HABF7E3F7_A592_443D_A341_2D1F211B53B9
#define HABF7E3F7_A592_443D_A341_2D1F211B53B9

#include "easy_graph/graph/node.h"
#include <type_traits>

EG_NS_BEGIN

template<typename ...TS>
auto makeNode(const NodeId& id, TS && ...ts) {
	Node node(id);
	if constexpr (sizeof...(ts) > 0) {
		makeNodeImpl(node, std::forward<TS>(ts)...);
	}
	return node;
}

template<typename T, typename ... TS>
void makeNodeImpl(Node& node, T && t, TS && ...ts) {
	if constexpr (std::is_same_v<Subgraph, std::decay_t<T>>) {
		node.addSubgraph(std::forward<T>(t));
	} else if constexpr (std::is_same_v<BoxPtr, std::decay_t<T>>) {
		node.packing(std::forward<T>(t));
	} else if constexpr (std::is_same_v<Attribute, std::decay_t<T>>) {
		node.setAttr(std::forward<T>(t));
	} else if constexpr (std::is_same_v<Attributes, std::decay_t<T>>) {
		node.mergeAttrs(std::forward<T>(t));
	} else {
		static_assert(!sizeof(T), "Unsupported node construction type!");
	}
	if constexpr (sizeof...(ts) > 0) {
		makeNodeImpl(node, std::forward<TS>(ts)...);
	}
}

#define NODE_OF(...)		::EG_NS::makeNode(__VA_ARGS__)

EG_NS_END

#endif
