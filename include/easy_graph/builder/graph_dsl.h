#ifndef H46D07001_D54E_497C_B1BA_878A47164DA5
#define H46D07001_D54E_497C_B1BA_878A47164DA5

#include "easy_graph/builder/graph_builder.h"
#include "easy_graph/builder/chain_builder.h"
#include "easy_graph/builder/box_builder.h"
#include "easy_graph/infra/macro_traits.h"

EG_NS_BEGIN

namespace detail {
	template<typename GRAPH_BUILDER>
	Graph build_graph(const char* name, GRAPH_BUILDER builderInDSL) {
		GraphBuilder builder(name);
		builderInDSL(builder);
		return std::move(*builder);
	}
}

#define SPECIFIED_NAME(...)   MACRO_CONDITION(VA_ARGS_NUM(__VA_ARGS__))
#define GRAPH(G, ...)         Graph G = ::EG_NS::detail::build_graph(SPECIFIED_NAME(__VA_ARGS__)(#__VA_ARGS__, #G), [&](GraphBuilder& BUILDER)
#define DATA_CHAIN(...)       ::EG_NS::ChainBuilder(BUILDER, EdgeType::DATA_EDGE) -> __VA_ARGS__
#define CTRL_CHAIN(...)       ::EG_NS::ChainBuilder(BUILDER, EdgeType::CTRL_EDGE) -> __VA_ARGS__
#define CHAIN(...)            DATA_CHAIN(__VA_ARGS__)
#define NODE(NAME, TYPE, ...) ::EG_NS::Node NAME(#NAME, BOX_OF(TYPE, ##__VA_ARGS__))

EG_NS_END

#endif
