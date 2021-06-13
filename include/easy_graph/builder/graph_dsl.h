#ifndef H46D07001_D54E_497C_B1BA_878A47164DA5
#define H46D07001_D54E_497C_B1BA_878A47164DA5

#include "easy_graph/builder/graph_builder.h"
#include "easy_graph/builder/chain_builder.h"
#include "easy_graph/builder/box_builder.h"
#include "easy_graph/builder/default_edge_type.h"
#include "easy_graph/graph/edge_type.h"

EG_NS_BEGIN

////////////////////////////////////////////////////////////////
namespace detail {
	constexpr const char* getGraphName(const char* defaultName,
										 const char* specifiedName = nullptr) {
		return specifiedName ? specifiedName : defaultName;
	}

	template<typename GRAPH_BUILDER>
	Graph buildGraph(const char* name, GRAPH_BUILDER builderInDSL) {
		GraphBuilder builder(name);
		builderInDSL(builder);
		return std::move(*builder);
	}
}

////////////////////////////////////////////////////////////////
#define NODE(NAME, TYPE, ...) ::EG_NS::Node NAME(#NAME, BOX_OF(TYPE, ##__VA_ARGS__))

#define CHAIN(...)            ::EG_NS::ChainBuilder(BUILDER, DEFAULT_EDGE_TYPE) -> __VA_ARGS__
#define DATA_CHAIN(...)       ::EG_NS::ChainBuilder(BUILDER, EdgeType::DATA()) -> __VA_ARGS__
#define CTRL_CHAIN(...)       ::EG_NS::ChainBuilder(BUILDER, EdgeType::CTRL()) -> __VA_ARGS__

#define ATTR(...)               Attribute(__VA_ARGS__)
#define ATTRS(...)              Attributes({__VA_ARGS__})

#define SUB_G(G, ...)           Subgraph(::EG_NS::detail::getGraphName(#G, ##__VA_ARGS__), G)

#define GRAPH(G, ...)           Graph G = ::EG_NS::detail::buildGraph(										\
													     ::EG_NS::detail::getGraphName(#G, ##__VA_ARGS__),	\
												           [&](GraphBuilder& BUILDER)

EG_NS_END

#endif
