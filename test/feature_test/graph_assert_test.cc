#include <cctest/cctest.h>
#include "easy_graph/builder/graph_dsl.h"
#include "easy_graph/assert/graph_assert.h"
#include "easy_graph/assert/node_assert.h"
#include "easy_graph/assert/edge_assert.h"
#include "easy_graph/edges/default_edge_type_register.h"

USING_EG_NS

REG_DEFAULT_EDGE_TYPE(data_edge());

FIXTURE(GraphAssertTest) {

	GRAPH(g1, "subgraph") {
		CHAIN(Node("a") -> Node("b", attr_of("sink", true)));
	};

	GRAPH(sample) {
		auto subgraph = subgraph_of(g1, "se", iw_of(1, ep_of("a", 1)));

		CHAIN(Node("a") -> Node("b") -> Node("c") -> Node("d") -> Node("e", subgraph));
		CHAIN(Node("a") -> Data(1, 1) -> Node("b") -> Edge(ctrl_edge(), attr_of("label", "to")) -> Node("e"));
	};

	TEST("should assert graph info") {

		ASSERT_GRAPH(sample) {
			ASSERT_EQ("sample", graph.name);
			ASSERT_EQ(5       , graph.nodeCount);
			ASSERT_EQ(6       , graph.edgeCount);
		};

		ASSERT_GRAPH(sample) {
			ASSERT_TRUE(graph.hasNode("a"));
			ASSERT_TRUE(graph.hasNode("b"));
			ASSERT_TRUE(graph.hasNode("c"));
			ASSERT_TRUE(graph.hasNode("d"));
			ASSERT_TRUE(graph.hasNode("e"));
		};

		ASSERT_GRAPH(sample) {
			ASSERT_TRUE(graph.hasEdge(edge_of("a", "b")));
			ASSERT_TRUE(graph.hasEdge(edge_of("b", "c")));
			ASSERT_TRUE(graph.hasEdge(edge_of("c", "d")));
			ASSERT_TRUE(graph.hasEdge(edge_of("b", "e", ctrl_edge())));
			ASSERT_TRUE(graph.hasEdge(edge_of("d", "e", data_edge())));
		};

		ASSERT_GRAPH(sample) {
			ASSERT_FALSE(graph.hasNode("f"));
			ASSERT_FALSE(graph.hasEdge(edge_of("a", "e")));
			ASSERT_FALSE(graph.hasEdge(edge_of("e", "f")));
			ASSERT_FALSE(graph.hasEdge(edge_of("c", "d", ctrl_edge())));
			ASSERT_FALSE(graph.hasEdge(edge_of(ep_of("a", 1), ep_of("b", 0))));
			ASSERT_FALSE(graph.hasEdge(edge_of(ep_of("a"), ep_of("b"), ctrl_edge())));
		};

		ASSERT_GRAPH(sample) {
			GRAPH(g1) {
				CHAIN(Node("a") -> Node("b"));
			};

			GRAPH(expect) {
				CHAIN(Node("a") -> Node("b") -> Node("c") -> Node("d") -> Node("e", subgraph_of(g1, iw_of(1, ep_of("a", 1)))));
				CHAIN(Node("a") -> Data(1, 1) -> Node("b"));
				CHAIN(Node("b") -> Edge(ctrl_edge()) -> Node("e"));
			};

			ASSERT_GRAPH_EQ(expect);
		};
	}

	TEST("should assert node info") {

		ASSERT_NODE(g1, "b") {
			ASSERT_EQ(1, node.inputCount);
			ASSERT_EQ(0, node.outputCount);
			ASSERT_EQ(0, node.subgraphCount);
			ASSERT_TRUE(node.getAttr<bool>("sink"));
			ASSERT_TRUE(*node.getAttr<bool>("sink"));
			ASSERT_FALSE(node.getAttr<bool>("source"));
		};

		ASSERT_NODE(sample, "a") {
			ASSERT_EQ(0, node.inputCount);
			ASSERT_EQ(2, node.outputCount);
		};

		ASSERT_NODE(sample, "a") {
			ASSERT_TRUE(node.isSource());
			ASSERT_TRUE(node.prevNextTo("b"));
		};

		ASSERT_NODE(sample, "a") {
			ASSERT_FALSE(node.isSink());
			ASSERT_FALSE(node.isIsolated());
			ASSERT_FALSE(node.prevNextTo("d"));
		};

		ASSERT_NODE(sample, "b") {
			ASSERT_TRUE(node.prevNextTo("c"));
			ASSERT_TRUE(node.postNextTo("a"));
		};

		ASSERT_NODE(sample, "e") {
			ASSERT_EQ(1, node.subgraphCount);
			ASSERT_TRUE(node.isSink());
			ASSERT_TRUE(node.postNextTo("d"));
			ASSERT_TRUE(node.hasSubgraph("se"));
			ASSERT_FALSE(node.hasSubgraph("subgraph"));
		};
	}

	TEST("should assert edge info") {
		ASSERT_EDGE(sample, edge_of("b", "e", ctrl_edge())) {
			ASSERT_TRUE(edge.getAttr<const char*>("label"));
			ASSERT_EQ("to", *edge.getAttr<const char*>("label"));
			ASSERT_FALSE(edge.getAttr<const char*>("cond"));
		};
	}
};
