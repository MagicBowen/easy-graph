#include "easy_graph/builder/graph_dsl.h"
#include "easy_graph/layout/graph_layout.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_layout_engine.h"

USING_EG_NS

int main() {

	/////////////////////////////////////////////////
	///  global layout configuration
	/////////////////////////////////////////////////

	GraphEasyLayoutEngine executor;

	GraphEasyOption options;
	options.format = LayoutFormat::BOXART;
    options.output = LayoutOutput::CONSOLE;
	options.dir = FlowDir::LR;
	options.type = LayoutType::FREE;
	options.scale = 1;

	GraphLayout::getInstance().config(executor, &options);

	/////////////////////////////////////////////////
	///  basic graph
	/////////////////////////////////////////////////

	GRAPH(g1) {
		CHAIN(Node("a") -> Node("b") -> Node("c") -> Node("d") -> Node("e"));
	});

	g1.layout();

	/////////////////////////////////////////////////
	///  graph with ctrl and data edge
	/////////////////////////////////////////////////

	GRAPH(g2) {
		CHAIN(Node("a") -> Edge(EDGE_CTRL, ATTR("label", "to")) -> Node("b") -> Node("c") -> Node("d") -> Node("e"));
		CHAIN(Node("a") -> Ctrl(ATTR("label", "condition")) -> Node("c"));
	});

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
		DATA_CHAIN(Node(b) -> Node("d"));
	});

	g3.layout();

	/////////////////////////////////////////////////
	///  graph with multiple nodes
	/////////////////////////////////////////////////

	GRAPH(g4) {
		CHAIN(Node("a") -> Node("b") -> Node("d") -> Node("f"));
		CHAIN(Node("a") -> Node("c") -> Node("e") -> Node("f"));
		CHAIN(Node("a") -> Node("d") -> Node("e"));
		CHAIN(Node("a") -> Node("e"));
		CHAIN(Node("a") -> Node("f"));
	});

	g4.layout();

	/////////////////////////////////////////////////
	///  specify the out&in port id of edge
	/////////////////////////////////////////////////

	GRAPH(g5) {
		CHAIN(Node("a") -> Node("b") -> Ctrl(ATTR("label", "condition")) -> Node("c") -> Node("d") -> Data(1, 1) -> Node("e"));
		CHAIN(Node("a") -> Data(0, 1) -> Node("c") -> Ctrl(ATTRS({"label", "to"}, {"border", true})) -> Node("e"));
		CHAIN(Node("a") -> Data(1, 0) -> Node("d"));
		CHAIN(Node("b") -> Node("e"));
		CHAIN(Node("c") -> Node("e"));
	});

	g5.layout();

	/////////////////////////////////////////////////
	///  node with attributes
	/////////////////////////////////////////////////

	GRAPH(g6) {
		CHAIN(Node("a", ATTRS({"source", true}, {"length", 3})) -> Data(1, 0) -> Node("d"));
		CHAIN(Node("b") -> Node("e"));
		CHAIN(Node("c") -> Node("e"));
	});

	g6.layout();

	/////////////////////////////////////////////////
	///  node with subgraphs
	/////////////////////////////////////////////////

	GRAPH(cond, "condition") {
		CTRL_CHAIN(Node("a") -> Node("b"));
	});

	GRAPH(body) {
		CHAIN(Node("a") -> Node("b") -> Node("c"));
	});

	GRAPH(graph) {
		auto sg_cond = SUBGRAPH_OF(cond, InputWire(0, Endpoint("a", 1)));
		auto sg_body = SUBGRAPH_OF(body, OutputWire(Endpoint("c", 1), 1));

		HAS_NODE(foreach, sg_cond, sg_body, ATTR("loop", true));
		HAS_NODE(loop, sg_cond, SUBGRAPH(body, "loop body", OutputWire(Endpoint("b", 1), 0)));

		DATA_CHAIN(Node("const_1") -> Node(loop) -> Node("unique") -> Node("softmax"));
		DATA_CHAIN(Node("const_2") -> Node("while", SUBGRAPH(cond, InputWire(1, Endpoint("a", 1))), SUBGRAPH(body, "while body")));
		CTRL_CHAIN(Node("case") -> Node("unique"));
		CTRL_CHAIN(Node(loop) -> Node(foreach));
	});

	graph.layout();
}
