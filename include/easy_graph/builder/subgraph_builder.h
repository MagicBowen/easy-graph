#ifndef H34CF11C9_D96A_4FBB_B532_1D3766B7640E
#define H34CF11C9_D96A_4FBB_B532_1D3766B7640E

#include "easy_graph/graph/subgraph.h"
#include <type_traits>

EG_NS_BEGIN

namespace detail {
	static inline void make_subgraph(Subgraph&) {
	}

	template<typename T, typename ... TS>
	void make_subgraph(Subgraph& subgraph, T && t, TS && ...ts) {
		if constexpr (std::is_convertible_v<std::decay_t<T>, std::string>) {
			subgraph.setName(std::forward<T>(t));
		} else if constexpr (std::is_same_v<InputWire, std::decay_t<T>>) {
			subgraph.wireUp(std::forward<T>(t));
		} else if constexpr (std::is_same_v<OutputWire, std::decay_t<T>>) {
			subgraph.wireUp(std::forward<T>(t));
		} else {
			static_assert(!sizeof(T), "Unsupported subgraph construction type!");
		}
		make_subgraph(subgraph, std::forward<TS>(ts)...);
	}
}

template<typename ...TS>
auto subgraph_of(const Graph& graph, TS && ...ts) {
	Subgraph subgraph(graph);
	detail::make_subgraph(subgraph, std::forward<TS>(ts)...);
	return subgraph;
}

EG_NS_END

#endif
