#include "graph_dsl.h"

USING_EG_NS

int main() {

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
		CHAIN(NODE("a") -> NODE("b") -> NODE("d") -> NODE("f"));
		CHAIN(NODE("a") -> NODE("c") -> NODE("e") -> NODE("f"));
		CHAIN(NODE("a") -> NODE("d") -> NODE("e"));
		CHAIN(NODE("a") -> NODE("e"));
		CHAIN(NODE("a") -> NODE("f"));
	});

	g3.layout(FLOW_TB);

	GRAPH(g4) {
		Node a("a"), b("b"), c("c");

		DATA_CHAIN(NODE(a) -> NODE(b) -> NODE(c) -> NODE("d") -> NODE("e"));
		CTRL_CHAIN(NODE(a) -> NODE("e"));
		DATA_CHAIN(NODE(b) -> NODE("d"));
	});

	g4.layout();

//	GRAPH(g5) {
////		CHAIN(NODE("a") -> JOINT(0, 1) -> NODE("b"));
//	});

	GRAPH(graph) {
		DATA_CHAIN(NODE("const_1") -> NODE("add") -> NODE("unique") -> NODE("softmax"));
		DATA_CHAIN(NODE("const_2") -> NODE("add"));
		CTRL_CHAIN(NODE("case") -> NODE("unique"));
	});

	graph.layout();
}
