#include <cctest/cctest.h>
#include "easy_graph/builder/graph_dsl.h"
#include "easy_graph/graph/subgraph.h"
#include "assertion/graph_assert.h"
#include "assertion/node_assert.h"
#include "assertion/edge_assert.h"

USING_EG_NS

FIXTURE(GraphAssertTest) {
	GRAPH(g1, "subgraph") {
		CHAIN(Node("a") -> Node("b"));
	});

	GRAPH(sample) {
		CHAIN(Node("a") -> Node("b") -> Node("c") -> Node("d") -> Node("e", Subgraph{g1}));
		CHAIN(Node("a") -> Data(1, 1) -> Node("b") -> Edge(EdgeType::CTRL) -> Node("e"));
	});

	TEST("should assert graph info") {

		ASSERT_GRAPH(sample) {
			ASSERT_EQ("sample", graph.name);
			ASSERT_EQ(5       , graph.nodeCount);
			ASSERT_EQ(6       , graph.edgeCount);
		});

		ASSERT_GRAPH(sample) {
			ASSERT_TRUE(graph.hasNode("a"));
			ASSERT_TRUE(graph.hasNode("b"));
			ASSERT_TRUE(graph.hasNode("c"));
			ASSERT_TRUE(graph.hasNode("d"));
			ASSERT_TRUE(graph.hasNode("e"));
		});

		ASSERT_GRAPH(sample) {
			ASSERT_TRUE(graph.hasEdge("a", "b"));
			ASSERT_TRUE(graph.hasEdge("b", "c"));
			ASSERT_TRUE(graph.hasEdge("c", "d"));
			ASSERT_TRUE(graph.hasEdge("b", "e", EdgeType::CTRL));
			ASSERT_TRUE(graph.hasEdge("d", "e", EdgeType::DATA));
		});

		ASSERT_GRAPH(sample) {
			ASSERT_TRUE(graph.hasEdge(Endpoint{"a", 0}, {"b", 0}));
			ASSERT_TRUE(graph.hasEdge(Endpoint{"c", 0}, {"d", 0}, EdgeType::DATA));
		});

		ASSERT_GRAPH(sample) {
			ASSERT_FALSE(graph.hasNode("f"));
			ASSERT_FALSE(graph.hasEdge("a", "e"));
			ASSERT_FALSE(graph.hasEdge("e", "f"));
			ASSERT_FALSE(graph.hasEdge("c", "d", EdgeType::CTRL));
			ASSERT_FALSE(graph.hasEdge(Endpoint{"a", 1}, {"b", 0}));
			ASSERT_FALSE(graph.hasEdge(Endpoint{"a", 0}, {"b", 0}, EdgeType::CTRL));
		});

		ASSERT_GRAPH(sample) {
			GRAPH(g1) {
				CHAIN(Node("a") -> Node("b"));
			});

			GRAPH(expect) {
				CHAIN(Node("a") -> Node("b") -> Node("c") -> Node("d") -> Node("e", Subgraph{"g1", g1}));
				CHAIN(Node("a") -> Data(1, 1) -> Node("b"));
				CHAIN(Node("b") -> Edge(EdgeType::CTRL) -> Node("e"));
			});

			ASSERT_TRUE(graph.isEqualTo(expect));
		});
	}

	TEST("should assert node info") {

		ASSERT_NODE(sample, "a") {
			ASSERT_EQ(0, node.inputCount);
			ASSERT_EQ(2, node.outputCount);
		});

		ASSERT_NODE(sample, "a") {
			ASSERT_TRUE(node.isSource());
			ASSERT_TRUE(node.prevNextTo("b"));
		});

		ASSERT_NODE(sample, "a") {
			ASSERT_FALSE(node.isSink());
			ASSERT_FALSE(node.isIsolated());
			ASSERT_FALSE(node.prevNextTo("d"));
		});

		ASSERT_NODE(sample, "b") {
			ASSERT_TRUE(node.prevNextTo("c"));
			ASSERT_TRUE(node.postNextTo("a"));
		});

		ASSERT_NODE(sample, "e") {
			ASSERT_TRUE(node.isSink());
			ASSERT_TRUE(node.postNextTo("d"));
		});
	}

	TEST("should assert edge info") {

		ASSERT_EDGE(sample, "a", "b") {
			ASSERT_EQ(2, edge.count);
			ASSERT_TRUE(edge.linked(0, 0));
			ASSERT_TRUE(edge.linked(1, 1));
			ASSERT_TRUE(edge.isDataType(0, 0));
			ASSERT_TRUE(edge.isDataType(1, 1));
			ASSERT_FALSE(edge.linked(0, 1));
		});

		ASSERT_EDGE(sample, "b", "e") {
			ASSERT_EQ(1, edge.count);
			ASSERT_TRUE(edge.isCtrlType());
		});
	}
};
