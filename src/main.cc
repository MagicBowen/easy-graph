#include "easy_graph/builder/graph_dsl.h"
#include "easy_graph/layout/graph_layout.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_executor.h"

USING_EG_NS

int main() {

	///////////////////////////////////////////////////////////////
	// global layout config

	GraphEasyExecutor executor;

	GraphEasyOption options;
	options.format = LayoutFormat::BOXART;
    options.output = LayoutOutput::CONSOLE;
	options.dir = FlowDir::LR;
	options.type = LayoutType::FREE;
	options.scale = 1;

	GraphLayout::getInstance().config(executor, &options);

	///////////////////////////////////////////////////////////////
	// basic graph

	GRAPH(g1) {
		CHAIN(NODE("a") -> NODE("b") -> NODE("c") -> NODE("d") -> NODE("e"));
	});

	g1.layout();

	///////////////////////////////////////////////////////////////
	// graph with ctrl and data edge

	GRAPH(g2) {
		CHAIN(NODE("a") -> CTRL("omit") -> NODE("b") -> NODE("c") -> DATA("copy") -> NODE("d") -> NODE("e"));
		CHAIN(NODE("a") -> CTRL("condition") -> NODE("c"));
	});

	g2.layout();

	///////////////////////////////////////////////////////////////
	// specified ctrl or data chain type and use pre-defined nodes

	GRAPH(g3) {
		Node a("a"), b("b"), c("c");

		DATA_CHAIN(NODE(a) -> NODE(b) -> NODE(c) -> NODE("d") -> NODE("e"));
		CTRL_CHAIN(NODE(a) -> NODE("e"));
		DATA_CHAIN(NODE(b) -> NODE("d"));
	});

	g3.layout();

	///////////////////////////////////////////////////////////////
	// graph with multiple nodes


	GRAPH(g4) {
		CHAIN(NODE("a") -> NODE("b") -> NODE("d") -> NODE("f"));
		CHAIN(NODE("a") -> NODE("c") -> NODE("e") -> NODE("f"));
		CHAIN(NODE("a") -> NODE("d") -> NODE("e"));
		CHAIN(NODE("a") -> NODE("e"));
		CHAIN(NODE("a") -> NODE("f"));
	});

	g4.layout();

	///////////////////////////////////////////////////////////////
	// specify the out&in port id of edge

	GRAPH(g5) {
		CHAIN(NODE("a") -> DATA("to") -> NODE("b") -> CTRL("condition") -> NODE("c") -> NODE("d") -> DATA(1, 1) -> NODE("e"));
		CHAIN(NODE("a") -> DATA(0, 1) -> NODE("c") -> CTRL() -> NODE("e"));
		CHAIN(NODE("a") -> DATA(1, 0) -> NODE("d"));
		CHAIN(NODE("b") -> NODE("e"));
		CHAIN(NODE("c") -> NODE("e"));
	});

	g5.layout();

	///////////////////////////////////////////////////////////////
	// node with subgraphs

	GRAPH(Cond) {
		CTRL_CHAIN(NODE("a") -> NODE("b"));
	});

	GRAPH(Body) {
		CHAIN(NODE("a") -> NODE("b") -> NODE("c"));
	});

	GRAPH(graph) {
		Node loop("loop", Cond, Body);
		Node foreach("foreach", Cond, Body);
		DATA_CHAIN(NODE("const_1") -> NODE(loop) -> NODE("unique") -> NODE("softmax"));
		DATA_CHAIN(NODE("const_2") -> NODE("while", Cond, Body));
		CTRL_CHAIN(NODE("case") -> NODE("unique"));
		CTRL_CHAIN(NODE(loop) -> NODE(foreach));
	});

	graph.layout();
}
