#include "graph_dsl.h"
#include "graph_layout.h"
#include "layout_option.h"

USING_EG_NS

int main() {

	GraphLayout::config(LayoutOption{.dir = FlowDir::LR, .type = LayoutType::FREE, .scale = 1});

	GRAPH(g1) {
		CHAIN(NODE("a") -> NODE("b") -> NODE("c") -> NODE("d") -> NODE("e"));
	});

	g1.layout();

	GRAPH(g2) {
		CHAIN(NODE("a") -> CTRL("omit") -> NODE("b") -> NODE("c") -> DATA("copy") -> NODE("d") -> NODE("e"));
		CHAIN(NODE("a") -> CTRL("condition") -> NODE("c"));
	});

	g2.layout();

	GRAPH(g3) {
		Node a("a"), b("b"), c("c");

		DATA_CHAIN(NODE(a) -> NODE(b) -> NODE(c) -> NODE("d") -> NODE("e"));
		CTRL_CHAIN(NODE(a) -> NODE("e"));
		DATA_CHAIN(NODE(b) -> NODE("d"));
	});

	g3.layout();


	GRAPH(g4) {
		CHAIN(NODE("a") -> NODE("b") -> NODE("d") -> NODE("f"));
		CHAIN(NODE("a") -> NODE("c") -> NODE("e") -> NODE("f"));
		CHAIN(NODE("a") -> NODE("d") -> NODE("e"));
		CHAIN(NODE("a") -> NODE("e"));
		CHAIN(NODE("a") -> NODE("f"));
	});

	g4.layout();

	GRAPH(g5) {
		CHAIN(NODE("a") -> DATA("to") -> NODE("b") -> CTRL("condition") -> NODE("c") -> NODE("d") -> DATA(1, 1) -> NODE("e"));
		CHAIN(NODE("a") -> DATA(0, 1) -> NODE("c") -> CTRL() -> NODE("e"));
		CHAIN(NODE("a") -> DATA(1, 0) -> NODE("d"));
		CHAIN(NODE("b") -> NODE("e"));
		CHAIN(NODE("c") -> NODE("e"));
	});

	g5.layout();

	GRAPH(Cond) {
		CTRL_CHAIN(NODE("a") -> NODE("b"));
	});

	GRAPH(Body) {
		CHAIN(NODE("a") -> NODE("b") -> NODE("c"));
	});

	GRAPH(graph) {
		Node loop("loop", Cond, Body);
		DATA_CHAIN(NODE("const_1") -> NODE("loop") -> NODE("unique") -> NODE("softmax"));
		DATA_CHAIN(NODE("const_2") -> NODE("add"));
		CTRL_CHAIN(NODE("case") -> NODE("unique"));
	});

	graph.layout();
}
