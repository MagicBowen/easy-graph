#ifndef HAF54D894_EE19_492A_940E_D0B3449C3016
#define HAF54D894_EE19_492A_940E_D0B3449C3016

#include "easy_graph/checker/visitor/node_check_visitor.h"
#include "easy_graph/graph/node_id.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/infra/log.h"

EG_NS_BEGIN

namespace detail {
	struct NodeChecker {
		NodeChecker(const Graph& graph, const NodeId& nodeId)
		: graph(graph), nodeId(nodeId) {
		}

		template<typename USER_ASSERT>
		auto operator | (USER_ASSERT && nodeAssert) {
			auto node = graph.findNode(nodeId);
			if (!node) EG_FATAL("Node(%s) not found in graph(%s)", nodeId, graph.getName());
			NodeCheckVisitor visitor(*node);
			graph.accept(visitor);
			try {
				std::forward<USER_ASSERT>(nodeAssert)(visitor);
			} catch(std::exception& e) {
				EG_ERR("Graph(%s)' node(%s) assert failed!\n%s", graph.getName(), nodeId, e.what());
				throw(e);
			}
		}

	private:
		const Graph& graph;
		const NodeId& nodeId;
	};
}

#define CHECK_NODE(GRAPH, NODE_ID)  ::EG_NS::detail::NodeChecker(GRAPH, NODE_ID) | [&](const NodeCheckVisitor& node)

EG_NS_END

#endif
