#ifndef H7D82AF79_7C21_4FF8_9AFB_4BB7FFF9B86D
#define H7D82AF79_7C21_4FF8_9AFB_4BB7FFF9B86D

#include "easy_graph/assert/visitor/graph_assert_visitor.h"
#include "easy_graph/assert/assert_error.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/infra/log.h"

EG_NS_BEGIN

namespace detail {
	template<typename GRAPH_ASSERT>
	void assert_graph(const Graph& graph, GRAPH_ASSERT graphAssert) {
		GraphAssertVisitor visitor;
		graph.accept(visitor);
		try {
			graphAssert(visitor);
		} catch(std::exception& e) {
			EG_ERR("Graph(%s) assert failed!\n%s", graph.getName().c_str(), e.what());
			throw(e);
		}
	}
}

#define ASSERT_GRAPH(GRAPH)  ::EG_NS::detail::assert_graph(GRAPH, [&](const GraphAssertVisitor& graph)

#define ASSERT_GRAPH_EQ(expect)						\
		if (!graph.isEqualTo(expect)) {				\
			graph.dump();							\
			expect.layout();						\
			throw AssertError(__FILE__, __LINE__, 	\
				"graph is not equal to expected!");	\
		}

EG_NS_END

#endif
