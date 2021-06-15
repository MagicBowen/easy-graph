#ifndef H34CF11C9_D96A_4FBB_B532_1D3766B7640E
#define H34CF11C9_D96A_4FBB_B532_1D3766B7640E

#include "easy_graph/graph/subgraph.h"
#include <type_traits>

EG_NS_BEGIN

template<typename ...TS>
auto make_subgraph(const Graph& graph, TS && ...ts) {
	Subgraph subgraph(graph);
	if constexpr (sizeof...(ts) > 0) {
		make_subgraph_impl(subgraph, std::forward<TS>(ts)...);
	}
	return subgraph;
}

template<typename T, typename ... TS>
void make_subgraph_impl(Subgraph& subgraph, T && t, TS && ...ts) {
	if constexpr (std::is_convertible_v<std::decay_t<T>, std::string>) {
		subgraph.setName(std::forward<T>(t));
	} else if constexpr (std::is_same_v<InputWire, std::decay_t<T>>) {
		subgraph.wireUp(std::forward<T>(t));
	} else if constexpr (std::is_same_v<OutputWire, std::decay_t<T>>) {
		subgraph.wireUp(std::forward<T>(t));
	} else {
		static_assert(!sizeof(T), "Unsupported subgraph construction type!");
	}
	if constexpr (sizeof...(ts) > 0) {
		make_subgraph_impl(subgraph, std::forward<TS>(ts)...);
	}
}

#define SUBGRAPH_OF(...)		::EG_NS::make_subgraph(__VA_ARGS__)

EG_NS_END

#endif
