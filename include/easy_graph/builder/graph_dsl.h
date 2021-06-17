#ifndef H46D07001_D54E_497C_B1BA_878A47164DA5
#define H46D07001_D54E_497C_B1BA_878A47164DA5

#include "easy_graph/builder/chain_builder.h"
#include "easy_graph/builder/box_builder.h"
#include "easy_graph/builder/subgraph_builder.h"
#include "easy_graph/builder/attrs_builder.h"
#include "easy_graph/builder/wire_builder.h"
#include "easy_graph/builder/endpoint_builder.h"

EG_NS_BEGIN

////////////////////////////////////////////////////////////////
namespace detail {
	constexpr const char* getGraphName(const char* defaultName,
									   const char* specifiedName = nullptr) noexcept {
		return specifiedName ? specifiedName : defaultName;
	}

	template<typename GRAPH_BUILDER>
	auto make_graph(const char* name, GRAPH_BUILDER builderInDSL) {
		GraphBuilder builder(name);
		builderInDSL(builder);
		return *builder;
	}
}

////////////////////////////////////////////////////////////////
#define CHAIN(...)            ::EG_NS::ChainBuilder(BUILDER, default_edge()) -> __VA_ARGS__
#define DATA_CHAIN(...)       ::EG_NS::ChainBuilder(BUILDER, data_edge()) -> __VA_ARGS__
#define CTRL_CHAIN(...)       ::EG_NS::ChainBuilder(BUILDER, ctrl_edge()) -> __VA_ARGS__

#define HAS_NODE(N, ...)       	auto N = node_of(#N, ##__VA_ARGS__);		\
								BUILDER->addNode(N)

#define GRAPH(G, ...)           Graph G = ::EG_NS::detail::make_graph(										\
													     ::EG_NS::detail::getGraphName(#G, ##__VA_ARGS__),	\
												           [&](GraphBuilder& BUILDER)

EG_NS_END

#endif
