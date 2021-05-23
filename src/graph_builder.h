#ifndef H5FED5F58_167D_4536_918A_D5FE8F28DD9C
#define H5FED5F58_167D_4536_918A_D5FE8F28DD9C

#include "graph.h"
#include "chain_builder.h"

EG_NS_BEGIN

namespace detail {
	template<typename GRAPH_BUILDER>
	Graph build_graph(const char* name, GRAPH_BUILDER buildGraph) {
		Graph g(name);
		buildGraph(g);
		return g;
	}
}

#define GRAPH(G) Graph G = ::EG_NS::detail::build_graph(#G, [](Graph& GR)

EG_NS_END

#endif
