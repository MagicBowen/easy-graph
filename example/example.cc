#include "easy_graph/builder/graph_dsl.h"
#include "easy_graph/layout/graph_layout.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_executor.h"

USING_EG_NS

int main() {

	/////////////////////////////////////////////////
	///  global layout configuration example
	/////////////////////////////////////////////////

	GraphEasyExecutor executor;

	GraphEasyOption options;
	options.format = LayoutFormat::BOXART;
    options.output = LayoutOutput::CONSOLE;
	options.dir = FlowDir::LR;
	options.type = LayoutType::FREE;
	options.scale = 1;

	GraphLayout::getInstance().config(executor, &options);

	/////////////////////////////////////////////////
	///  basic graph example
	/////////////////////////////////////////////////

	GRAPH(g1) {
		CHAIN(Node("a") -> Node("b") -> Node("c") -> Node("d") -> Node("e"));
	});

	g1.layout();

	/////////////////////////////////////////////////
	///  graph with ctrl and data edge
	/////////////////////////////////////////////////

	GRAPH(g2) {
		CHAIN(Node("a") -> Ctrl("omit") -> Node("b") -> Node("c") -> Data("copy") -> Node("d") -> Node("e"));
		CHAIN(Node("a") -> Ctrl("condition") -> Node("c"));
	});

	g2.layout();

	/////////////////////////////////////////////////
	///  specified chain with pre-defined nodes
	/////////////////////////////////////////////////

	GRAPH(g3) {
		Node a("a"), b("b"), c("c");

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
		CHAIN(Node("a") -> Data("to") -> Node("b") -> Ctrl("condition") -> Node("c") -> Node("d") -> Data(1, 1) -> Node("e"));
		CHAIN(Node("a") -> Data(0, 1) -> Node("c") -> Ctrl() -> Node("e"));
		CHAIN(Node("a") -> Data(1, 0) -> Node("d"));
		CHAIN(Node("b") -> Node("e"));
		CHAIN(Node("c") -> Node("e"));
	});

	g5.layout();

	/////////////////////////////////////////////////
	///  node with subgraphs
	/////////////////////////////////////////////////

	GRAPH(Cond) {
		CTRL_CHAIN(Node("a") -> Node("b"));
	});

	GRAPH(Body) {
		CHAIN(Node("a") -> Node("b") -> Node("c"));
	});

	GRAPH(graph) {
		Node loop("loop", Cond, Body);
		Node foreach("foreach", Cond, Body);
		DATA_CHAIN(Node("const_1") -> Node(loop) -> Node("unique") -> Node("softmax"));
		DATA_CHAIN(Node("const_2") -> Node("while", Cond, Body));
		CTRL_CHAIN(Node("case") -> Node("unique"));
		CTRL_CHAIN(Node(loop) -> Node(foreach));
	});

	graph.layout();
}
