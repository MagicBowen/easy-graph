#ifndef H4F77218F_964D_4BEC_ACA8_DD9846BC7507
#define H4F77218F_964D_4BEC_ACA8_DD9846BC7507

#include "easy_graph/assert/visitor/edge_assert_visitor.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/infra/log.h"

EG_NS_BEGIN

namespace detail {
	struct EdgeAssert {
		EdgeAssert(const Graph& graph, const Edge& edge)
		: graph(graph), edge(edge) {
		}

		template<typename USER_ASSERT>
		auto operator | (USER_ASSERT && edgeAssert) {
			auto result = graph.findEdge(edge);
			if (!result) {
				EG_FATAL("Edge not found in graph(%s)", graph.getName());
			}
			EdgeAssertVisitor visitor(*result);
			graph.accept(visitor);

			try {
				std::forward<USER_ASSERT>(edgeAssert)(visitor);
			} catch(std::exception& e) {
				EG_ERR("Edge of graph(%s) assert failed!\n%s", graph.getName(), e.what());
				throw(e);
			}
		}

	private:
		const Graph& graph;
		const Edge& edge;
	};
}

#define ASSERT_EDGE(GRAPH, EDGE)  ::EG_NS::detail::EdgeAssert(GRAPH, EDGE) | [&](const EdgeAssertVisitor& edge)

EG_NS_END

#endif
