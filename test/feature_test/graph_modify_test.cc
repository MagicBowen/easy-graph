#include <cctest/cctest.h>
#include "easy_graph/modifier/modifier_exec.h"
#include "easy_graph/assert/graph_assert.h"
#include "easy_graph/builder/graph_dsl.h"
#include "easy_graph/infra/status.h"

USING_EG_NS

FIXTURE(GraphModifyTest) {

	TEST("should erase node") {
		GRAPH(graph) {
			HAS_NODE(a);
			HAS_NODE(b);
		});

		modifier_exec(graph, NodeEraser("a"));

        ASSERT_GRAPH(graph) {
    		GRAPH(expect) {
    			HAS_NODE(b);
    		});
        	ASSERT_TRUE(graph.isEqualTo(expect));
        });
    }

	TEST("should erase edge") {
		GRAPH(graph) {
			CHAIN(Node("a") -> Node("b"));
		});

		modifier_exec(graph, EdgeEraser(edge_of("a", "b")));

        ASSERT_GRAPH(graph) {
    		GRAPH(expect) {
    			HAS_NODE(a);
    			HAS_NODE(b);
    		});
        	ASSERT_TRUE(graph.isEqualTo(expect));
        });
	}

	TEST("should erase edge with endpoint") {
		GRAPH(graph) {
			CHAIN(Node("a") -> Node("b"));
			CHAIN(Node("a") -> Edge(ctrl_edge(), pp_of(1, 1)) -> Node("b"));
		});

		modifier_exec(graph, EdgeEraser(edge_of(ep_of("a", 1), ep_of("b", 1))));

        ASSERT_GRAPH(graph) {
    		GRAPH(expect) {
    			CHAIN(Node("a") -> Node("b"));
    		});
        	ASSERT_TRUE(graph.isEqualTo(expect));
        });
	}

	TEST("should erase node and edge") {
		GRAPH(graph) {
			CHAIN(Node("a") -> Node("b") -> Node("c"));
		});

		modifier_exec(graph, NodeEraser("a"), EdgeEraser(edge_of("a", "b")));

        ASSERT_GRAPH(graph) {
    		GRAPH(expect) {
    			CHAIN(Node("b") -> Node("c"));
    		});
        	ASSERT_TRUE(graph.isEqualTo(expect));
        });
	}
};
