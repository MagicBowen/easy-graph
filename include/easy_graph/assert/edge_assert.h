#ifndef H4F77218F_964D_4BEC_ACA8_DD9846BC7507
#define H4F77218F_964D_4BEC_ACA8_DD9846BC7507

#include "easy_graph/assert/visitor/edge_assert_visitor.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/infra/log.h"

EG_NS_BEGIN

namespace detail {
	template<typename EDGE_ASSERT>
	void assert_edge(const Graph& graph, const Edge& e, EDGE_ASSERT edgeAssert) {
		auto edge = graph.findEdge(e);
		if (!edge) {
			EG_FATAL("Edge not found in graph(%s)", graph.getName());
		}
		EdgeAssertVisitor visitor(*edge);
		graph.accept(visitor);

		try {
			edgeAssert(visitor);

		} catch(std::exception& e) {
			EG_ERR("Edge of graph(%s) assert failed!\n%s", graph.getName(), e.what());
			throw(e);
		}
	}
}

#define ASSERT_EDGE(GRAPH, EDGE)  ::EG_NS::detail::assert_edge(GRAPH, EDGE, [&](const EdgeAssertVisitor& edge)


EG_NS_END

#endif
