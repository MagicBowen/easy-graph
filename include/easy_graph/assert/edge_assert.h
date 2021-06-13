#ifndef H4F77218F_964D_4BEC_ACA8_DD9846BC7507
#define H4F77218F_964D_4BEC_ACA8_DD9846BC7507

#include "easy_graph/assert/visitor/edge_assert_visitor.h"
#include "easy_graph/graph/node_id.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/infra/log.h"


EG_NS_BEGIN

namespace detail {
	template<typename EDGE_ASSERT>
	void assert_edge(const Graph& graph, const NodeId& src, const NodeId& dst, EDGE_ASSERT edgeAssert) {
		auto srcNode = graph.findNode(src);
		if (!srcNode) EG_FATAL("Source node(%s) not found in graph(%s)", src.c_str(), graph.getName().c_str());

		auto dstNode = graph.findNode(dst);
		if (!dstNode) EG_FATAL("Sink node(%s) not found in graph(%s)", dst.c_str(), graph.getName().c_str());

		EdgeAssertVisitor visitor(*srcNode, *dstNode);
		graph.accept(visitor);

		try {
			edgeAssert(visitor);

		} catch(std::exception& e) {
			EG_ERR("Graph(%s)'s edge(%s, %s) assert failed!\n%s", graph.getName().c_str(), src.c_str(), dst.c_str(), e.what());
			throw(e);
		}
	}
}

#define ASSERT_EDGE(GRAPH, SRC_NODE, DST_NODE)  ::EG_NS::detail::assert_edge(GRAPH, SRC_NODE, DST_NODE, [&](const EdgeAssertVisitor& edge)


EG_NS_END

#endif
