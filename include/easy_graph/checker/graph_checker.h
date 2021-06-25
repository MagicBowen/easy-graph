#ifndef H7D82AF79_7C21_4FF8_9AFB_4BB7FFF9B86D
#define H7D82AF79_7C21_4FF8_9AFB_4BB7FFF9B86D

#include "easy_graph/checker/visitor/graph_check_visitor.h"
#include "easy_graph/checker/check_error.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/infra/log.h"

EG_NS_BEGIN

namespace detail {
	struct GraphChecker {
		GraphChecker(const Graph& graph)
		: graph(graph) {
		}

		template<typename USER_ASSERT>
		auto operator | (USER_ASSERT && graphAssert) {
			GraphCheckVisitor visitor;
			graph.accept(visitor);
			try {
				std::forward<USER_ASSERT>(graphAssert)(visitor);
			} catch(std::exception& e) {
				EG_ERR("Graph(%s) assert failed!\n%s", graph.getName(), e.what());
				throw(e);
			}
		}

	private:
		const Graph& graph;
	};
}

#define CHECK_GRAPH(GRAPH)  ::EG_NS::detail::GraphChecker(GRAPH) | [&](const GraphCheckVisitor& graph)

#define ASSERT_GRAPH_EQ(expect)						\
		if (!graph.isEqualTo(expect)) {				\
			graph.dump();							\
			expect.layout();						\
			throw CheckError(__FILE__, __LINE__, 	\
				"graph is not equal to expected!");	\
		}

EG_NS_END

#endif
