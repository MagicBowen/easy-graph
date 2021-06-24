#include "easy_graph/builder/graph_dsl.h"
#include "easy_graph/layout/graph_layout.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_layout_engine.h"

USING_EG_NS

int main() {
	/////////////////////////////////////////////////
	///  basic graph
	/////////////////////////////////////////////////

	GRAPH(g1) {
		CHAIN(Node("a") -> Node("b") -> Node("c") -> Node("d") -> Node("e"));
	};

	g1.layout();

	/////////////////////////////////////////////////
	///  graph with ctrl and data edge
	/////////////////////////////////////////////////

	GRAPH(g2) {
		CHAIN(Node("a") -> Edge(1, 1) -> Node("b") -> Node("c") -> Node("d") -> Node("e"));
		CHAIN(Node("a") -> Edge(ctrl_edge(), attr_of("label", "condition")) -> Node("c"));
	};

	g2.layout();

	/////////////////////////////////////////////////
	///  specified chain with pre-defined nodes
	/////////////////////////////////////////////////

	GRAPH(g3) {
		HAS_NODE(a);
		HAS_NODE(b);
		HAS_NODE(c);

		DATA_CHAIN(Node(a) -> Node(b) -> Node(c) -> Node("d") -> Node("e"));
		DATA_CHAIN(Node(a) -> Node("e"));
		CTRL_CHAIN(Node(b) -> Node("d"));
	};

	g3.layout();

	/////////////////////////////////////////////////
	///  graph with multiple nodes
	/////////////////////////////////////////////////

	GRAPH(g4) {
		CHAIN(Node("a") -> Node("b") -> Node("d") -> Node("f", attr_of("sink", true)));
		CHAIN(Node("a") -> Node("c") -> Node("e") -> Node("f"));
		CHAIN(Node("a") -> Node("d") -> Node("e"));
		CHAIN(Node("a") -> Node("e"));
		CHAIN(Node("a") -> Node("f"));
	};

	g4.layout();

	/////////////////////////////////////////////////
	///  specify the out&in port id of edge
	/////////////////////////////////////////////////

	GRAPH(g5) {
		CHAIN(Node("a") -> Node("b") -> Ctrl(attr_of("label", "condition")) -> Node("c") -> Node("d") -> Data(1, 1) -> Node("e"));
		CHAIN(Node("a") -> Data(0, 1) -> Node("c") -> Ctrl(attrs_of({{"label", "to"}, {"border", true}})) -> Node("e"));
		CHAIN(Node("a") -> Data(1, 0) -> Node("d"));
		CHAIN(Node("b") -> Node("e"));
		CHAIN(Node("c") -> Node("e"));
	};

	g5.layout();

	/////////////////////////////////////////////////
	///  node with attributes
	/////////////////////////////////////////////////

	GRAPH(g6) {
		CHAIN(Node("a", attrs_of({{"source", true}, {"length", 3}})) -> Data(1, 0) -> Node("d"));
		CHAIN(Node("b") -> Node("e"));
		CHAIN(Node("c") -> Node("e"));
	};

	g6.layout();

	/////////////////////////////////////////////////
	///  node with subgraphs
	/////////////////////////////////////////////////

	GRAPH(cond, "condition") {
		CTRL_CHAIN(Node("a") -> Node("b"));
	};

	GRAPH(body) {
		CHAIN(Node("a") -> Node("b") -> Node("c"));
	};

	GRAPH(graph) {
		auto sg_cond = subgraph_of(cond, iw_of(0, ep_of("a", 1)));
		auto sg_body = subgraph_of(body, ow_of(ep_of("c", 1), 1));

		auto foreach = node_of("foreach", sg_cond, sg_body, attr_of("loop", true));
		auto loop    = node_of("loop", sg_cond, subgraph_of(body, "loop body", ow_of(ep_of("b", 1), 0)));

		DATA_CHAIN(Node("const_1") -> Node(loop) -> Node("unique") -> Node("softmax"));
		DATA_CHAIN(Node("const_2") -> Node("while", subgraph_of(cond, iw_of(1, ep_of("a", 1))), subgraph_of(body, "while body")));
		CTRL_CHAIN(Node("case") -> Node("unique"));
		CTRL_CHAIN(Node(loop) -> Node(foreach));
	};

	graph.layout();
}
