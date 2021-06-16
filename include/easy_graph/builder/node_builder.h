#ifndef HABF7E3F7_A592_443D_A341_2D1F211B53B9
#define HABF7E3F7_A592_443D_A341_2D1F211B53B9

#include "easy_graph/graph/node.h"
#include <type_traits>

EG_NS_BEGIN

namespace detail {
	static inline void make_node(Node&) {
	}

	template<typename T, typename ... TS>
	void make_node(Node& node, T && t, TS && ...ts) {
		if constexpr (std::is_same_v<Subgraph, std::decay_t<T>>) {
			node.addSubgraph(std::forward<T>(t));
		} else if constexpr (std::is_same_v<BoxPtr, std::decay_t<T>>) {
			node.packing(std::forward<T>(t));
		} else if constexpr (std::is_same_v<Attribute, std::decay_t<T>>) {
			node.setAttr(std::forward<T>(t));
		} else if constexpr (std::is_same_v<Attributes, std::decay_t<T>>) {
			node.replaceAttrs(std::forward<T>(t));
		} else {
			static_assert(!sizeof(T), "Unsupported node construction type!");
		}
		make_node(node, std::forward<TS>(ts)...);
	}
}

template<typename ...TS>
auto node_of(const NodeId& id, TS && ...ts) {
	Node node(id);
	detail::make_node(node, std::forward<TS>(ts)...);
	return node;
}

EG_NS_END

#endif
