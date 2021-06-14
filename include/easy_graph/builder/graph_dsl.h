#ifndef H46D07001_D54E_497C_B1BA_878A47164DA5
#define H46D07001_D54E_497C_B1BA_878A47164DA5

#include "easy_graph/builder/graph_builder.h"
#include "easy_graph/builder/chain_builder.h"
#include "easy_graph/builder/box_builder.h"
#include "easy_graph/builder/subgraph_builder.h"
#include "easy_graph/builder/edge_types/default_edge_type.h"
#include "easy_graph/builder/edge_types/ctrl_edge_type.h"
#include "easy_graph/builder/edge_types/data_edge_type.h"

EG_NS_BEGIN

////////////////////////////////////////////////////////////////
namespace detail {
	constexpr const char* getGraphName(const char* defaultName,
									   const char* specifiedName = nullptr) noexcept {
		return specifiedName ? specifiedName : defaultName;
	}

	template<typename GRAPH_BUILDER>
	auto buildGraph(const char* name, GRAPH_BUILDER builderInDSL) {
		GraphBuilder builder(name);
		builderInDSL(builder);
		return *builder;
	}
}

////////////////////////////////////////////////////////////////
#define CHAIN(...)            ::EG_NS::ChainBuilder(BUILDER, EDGE_DEFAULT) -> __VA_ARGS__
#define DATA_CHAIN(...)       ::EG_NS::ChainBuilder(BUILDER, EDGE_DATA) -> __VA_ARGS__
#define CTRL_CHAIN(...)       ::EG_NS::ChainBuilder(BUILDER, EDGE_CTRL) -> __VA_ARGS__

#define HAS_NODE(N, ...)       	auto N = NODE_OF(#N, ##__VA_ARGS__);		\
								BUILDER->addNode(N)

#define ATTR(...)               Attribute(__VA_ARGS__)
#define ATTRS(...)              Attributes({__VA_ARGS__})

#define SUBGRAPH(G, ...)        SUBGRAPH_OF(G, ##__VA_ARGS__)

#define GRAPH(G, ...)           Graph G = ::EG_NS::detail::buildGraph(										\
													     ::EG_NS::detail::getGraphName(#G, ##__VA_ARGS__),	\
												           [&](GraphBuilder& BUILDER)

EG_NS_END

#endif
