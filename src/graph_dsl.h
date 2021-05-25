#ifndef H46D07001_D54E_497C_B1BA_878A47164DA5
#define H46D07001_D54E_497C_B1BA_878A47164DA5

#include "graph_builder.h"
#include "chain_builder.h"

EG_NS_BEGIN

namespace detail {
	template<typename GRAPH_BUILDER>
	Graph build_graph(const char* name, GRAPH_BUILDER userBuildGraphWith) {
		GraphBuilder builder(name);
		userBuildGraphWith(builder);
		return std::move(builder.buildGraphDone());
	}
}

#define GRAPH(G) Graph G = ::EG_NS::detail::build_graph(#G, [&](GraphBuilder& BUILDER)

#define DATA_CHAIN(...) ::EG_NS::ChainBuilder(BUILDER, DATA_EDGE) -> __VA_ARGS__
#define CTRL_CHAIN(...) ::EG_NS::ChainBuilder(BUILDER, CTRL_EDGE) -> __VA_ARGS__
#define CHAIN(...) DATA_CHAIN(__VA_ARGS__)

EG_NS_END

#endif
