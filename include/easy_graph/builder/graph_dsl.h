#ifndef H46D07001_D54E_497C_B1BA_878A47164DA5
#define H46D07001_D54E_497C_B1BA_878A47164DA5

#include "easy_graph/builder/graph_builder.h"
#include "easy_graph/builder/chain_builder.h"
#include "easy_graph/builder/box_builder.h"

EG_NS_BEGIN

namespace detail {
	template<typename GRAPH_BUILDER>
	Graph build_graph(const char* name, GRAPH_BUILDER builderInDSL) {
		GraphBuilder builder(name);
		builderInDSL(builder);
		return std::move(builder.buildGraphDone());
	}
}

#define GRAPH(G) Graph G = ::EG_NS::detail::build_graph(#G, [&](GraphBuilder& BUILDER)

#define BOXING(TYPE, FUNC, ...) ::EG_NS::BoxBuilder(&TYPE::FUNC, __VA_ARGS__)
#define DATA_CHAIN(...) ::EG_NS::ChainBuilder(BUILDER, EdgeType::DATA_EDGE) -> __VA_ARGS__
#define CTRL_CHAIN(...) ::EG_NS::ChainBuilder(BUILDER, EdgeType::CTRL_EDGE) -> __VA_ARGS__
#define CHAIN(...)      DATA_CHAIN(__VA_ARGS__)

EG_NS_END

#endif
