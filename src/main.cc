#include "graph_builder.h"
#include "graph_layout.h"
#include "log.h"

USING_EG_NS

int main() {
	Graph g1 = GRAPH("graph_1") {
		CHAIN(NODE("a") -> NODE("b") -> NODE("c") -> NODE("d") -> NODE("e"));
	});

	GraphLayout::layout(g1);

	Graph g2 = GRAPH("graph_2") {
		CHAIN(NODE("a") -> NODE("b") -> NODE("c") -> NODE("d") -> NODE("e"));
		CHAIN(NODE("a") -> NODE("c"));
	});

	GraphLayout::layout(g2);

	Graph g3 = GRAPH("graph_3") {
		Node a("a"), b("b"), c("c");

		DATA_CHAIN(NODE(a) -> NODE(b) -> NODE(c) -> NODE("d") -> NODE("e"));
		CTRL_CHAIN(NODE(a) -> NODE("e"));
		DATA_CHAIN(NODE(b) -> NODE("d"));
	});

	GraphLayout::layout(g3);
}
