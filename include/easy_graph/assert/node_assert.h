#ifndef HAF54D894_EE19_492A_940E_D0B3449C3016
#define HAF54D894_EE19_492A_940E_D0B3449C3016

#include "easy_graph/assert/visitor/node_assert_visitor.h"
#include "easy_graph/graph/node_id.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/infra/log.h"

EG_NS_BEGIN

namespace detail {
	template<typename NODE_ASSERT>
	void assert_node(const Graph& graph, const NodeId& nodeId, NODE_ASSERT nodeAssert) {
		auto node = graph.findNode(nodeId);
		if (!node) EG_FATAL("Node(%s) not found in graph(%s)", nodeId.c_str(), graph.getName().c_str());
		NodeAssertVisitor visitor(*node);
		graph.accept(visitor);
		try {
			nodeAssert(visitor);
		} catch(std::exception& e) {
			EG_ERR("Graph(%s)' node(%s) assert failed!\n%s", graph.getName().c_str(), nodeId.c_str(), e.what());
			throw(e);
		}
	}
}

#define ASSERT_NODE(GRAPH, NODE_ID)  ::EG_NS::detail::assert_node(GRAPH, NODE_ID, [&](const NodeAssertVisitor& node)

EG_NS_END

#endif
