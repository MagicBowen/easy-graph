#include <cctest/cctest.h>
#include "easy_graph/modifier/graph_modify_executor.h"
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

		graph_modify_execute(graph, NodeEraser("a"));

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

		graph_modify_execute(graph, EdgeEraser(edge_of("a", "b")));

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
			CHAIN(Node("a") -> Edge(1, 1) -> Node("b"));
		});

		graph_modify_execute(graph, EdgeEraser(edge_of(ep_of("a", 1), ep_of("b", 1))));

        ASSERT_GRAPH(graph) {
    		GRAPH(expect) {
    			CHAIN(Node("a") -> Node("b"));
    		});
        	ASSERT_TRUE(graph.isEqualTo(expect));
        });
	}

	TEST("should erase edge with type") {
		GRAPH(graph) {
			CHAIN(Node("a") -> Node("b"));
			CHAIN(Node("a") -> Edge(ctrl_edge()) -> Node("b"));
		});

		graph_modify_execute(graph, EdgeEraser(edge_of("a", "b", data_edge())));

        ASSERT_GRAPH(graph) {
    		GRAPH(expect) {
    			CHAIN(Node("a") -> Edge(ctrl_edge()) -> Node("b"));
    		});
    		ASSERT_GRAPH_EQ(expect);
        });
	}

	TEST("should erase node and edge") {
		GRAPH(graph) {
			CHAIN(Node("a") -> Node("b") -> Node("c"));
		});

		graph_modify_execute(graph, NodeEraser("a"), EdgeEraser(edge_of("a", "b")));

        ASSERT_GRAPH(graph) {
    		GRAPH(expect) {
    			CHAIN(Node("b") -> Node("c"));
    		});
        	ASSERT_TRUE(graph.isEqualTo(expect));
        });
	}

	TEST("should add node and edge") {
		GRAPH(graph) {
			CHAIN(Node("a") -> Node("b"));
		});

		graph_modify_execute(graph, NodeAdder(node_of("c")), EdgeAdder(edge_of("b", "c")));

        ASSERT_GRAPH(graph) {
    		GRAPH(expect) {
    			CHAIN(Node("a") -> Node("b") -> Node("c"));
    		});
        	ASSERT_TRUE(graph.isEqualTo(expect));
        });
	}

	TEST("should omit error when not in transaction") {
		GRAPH(graph) {
			CHAIN(Node("a") -> Node("b"));
		});

		graph_modify_execute(graph, NodeAdder(node_of("c")), NodeEraser("d"));

        ASSERT_GRAPH(graph) {
    		GRAPH(expect) {
    			HAS_NODE(c);
    			CHAIN(Node("a") -> Node("b"));
    		});
        	ASSERT_TRUE(graph.isEqualTo(expect));
        });
	}

	TEST("should rollback graph when error in transaction") {
		GRAPH(graph) {
			CHAIN(Node("a") -> Node("b"));
		});

		graph_modify_atom_execute(graph, NodeAdder(node_of("c")), NodeEraser("d"));

        ASSERT_GRAPH(graph) {
    		GRAPH(expect) {
    			CHAIN(Node("a") -> Node("b"));
    		});
        	ASSERT_TRUE(graph.isEqualTo(expect));
        });
	}
};
