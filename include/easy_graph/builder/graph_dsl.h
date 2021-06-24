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
	struct GraphDefiner {
		GraphDefiner(const char* defaultName, const char* specifiedName = nullptr) {
			name = specifiedName ? specifiedName : defaultName;
		}

		template<typename USER_BUILDER>
		auto operator | (USER_BUILDER && userBuilder) {
			GraphBuilder graphBuilder{name};
			std::forward<USER_BUILDER>(userBuilder)(graphBuilder);
			return *graphBuilder;
		}

	private:
		const char* name;
	};
}

////////////////////////////////////////////////////////////////
#define CHAIN(...)            ::EG_NS::ChainBuilder(BUILDER, default_edge()) -> __VA_ARGS__
#define DATA_CHAIN(...)       ::EG_NS::ChainBuilder(BUILDER, data_edge()) -> __VA_ARGS__
#define CTRL_CHAIN(...)       ::EG_NS::ChainBuilder(BUILDER, ctrl_edge()) -> __VA_ARGS__

#define HAS_NODE(N, ...)        auto N = ::EG_NS::node_of(#N, ##__VA_ARGS__);		\
							    BUILDER->addNode(N)

#define GRAPH(G, ...)         ::EG_NS::Graph G = ::EG_NS::detail::GraphDefiner(#G, ##__VA_ARGS__) | [&](auto && BUILDER)

EG_NS_END

#endif
