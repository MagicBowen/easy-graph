#include <cctest/cctest.h>
#include "easy_graph/builder/graph_dsl.h"
#include "assertion/graph_assert.h"
#include "assertion/node_assert.h"

USING_EG_NS

FIXTURE(GraphAssertTest) {

	TEST("should assert graph info") {
		GRAPH(g1) {
			CHAIN(Node("a") -> Node("b") -> Node("c") -> Node("d") -> Node("e"));
		});

		ASSERT_GRAPH(g1) {
			ASSERT_EQ("g1", graph.name);
			ASSERT_EQ(5   , graph.nodeCount);
			ASSERT_EQ(4   , graph.edgeCount);
		});

		ASSERT_GRAPH(g1) {
			ASSERT_TRUE(graph.hasNode("a"));
			ASSERT_TRUE(graph.hasNode("b"));
			ASSERT_TRUE(graph.hasNode("c"));
			ASSERT_TRUE(graph.hasNode("d"));
			ASSERT_TRUE(graph.hasNode("e"));
		});

		ASSERT_GRAPH(g1) {
			ASSERT_TRUE(graph.hasEdge("a", "b"));
			ASSERT_TRUE(graph.hasEdge("b", "c"));
			ASSERT_TRUE(graph.hasEdge("c", "d"));
			ASSERT_TRUE(graph.hasEdge("d", "e"));
		});

		ASSERT_GRAPH(g1) {
			ASSERT_FALSE(graph.hasNode("f"));
			ASSERT_FALSE(graph.hasEdge("c", "e"));
			ASSERT_FALSE(graph.hasEdge("e", "f"));
		});

		ASSERT_GRAPH(g1) {
			GRAPH(expect) {
				CHAIN(Node("a") -> Node("b") -> Node("c"));
				CHAIN(Node("c") -> Node("d") -> Node("e"));
			});

			ASSERT_TRUE(graph.isEqualTo(expect));
		});
	}

	TEST("should assert node info") {

		GRAPH(g1) {
			CHAIN(Node("a") -> Node("b") -> Node("c"));
			CHAIN(Node("c") -> Node("d") -> Node("e"));
		});

		ASSERT_NODE(g1, "a") {
			ASSERT_EQ(0, node.prevEdgeCount);
			ASSERT_TRUE(node.prevNextTo("b"));
		});
	}
};
