#include "graph.h"
#include "node.h"
#include "edge.h"
#include "graph_layout.h"

USING_EG_NS

int main() {
	Graph g("graph");

	Node a("a");
	Node b("b");
	Node c("c");

	g.addNode(a);
	g.addNode(b);
	g.addNode(c);

	g.addEdge(Edge(DATA_EDGE, a, b));
	g.addEdge(Edge(CTRL_EDGE, b, c));
	g.addEdge(Edge(CTRL_EDGE, a, c));

	return GraphLayout(g).layout();
}
