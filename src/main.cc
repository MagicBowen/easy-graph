#include "chain_builder.h"
#include "graph_layout.h"
#include "graph.h"
#include "node.h"

USING_EG_NS

int main() {

//	auto g = [](const char* name) {
//		Graph g(name);
//		Node a("a");
//		Node b("b");
//		Node c("c");
//
//		DATA_CHAIN(g, NODE(a) -> NODE(b) -> NODE(c) -> NODE("d") -> NODE("e"));
//		CTRL_CHAIN(g, NODE(a) -> NODE(c) -> NODE("f") -> NODE("d"));
//		return std::move(g);
//	}("graph");

	Graph g("graph");
	Node a("a");
	Node b("b");
	Node c("c");

	DATA_CHAIN(g, NODE(a) -> NODE(b) -> NODE(c) -> NODE("d") -> NODE("e"));
	CTRL_CHAIN(g, NODE(a) -> NODE(c) -> NODE("f") -> NODE("d"));

	return GraphLayout::layout(g);
}
