#include "graph.h"
#include "node.h"
#include "edge.h"
#include "graph_layout.h"

USING_EG_NS

struct ChainBuilder {
	ChainBuilder(Graph& graph, EdgeType type = DATA_EDGE)
	: graph(graph),
	  nodeFromEgde(*this, type) {
	}

	struct ChainNodeBuilder {
		ChainNodeBuilder(ChainBuilder& chain, EdgeType edgeType)
		: chain(chain), edgeType(edgeType) {
		}
		ChainBuilder NODE(const Node& node) {
			return chain.addDstNodeOnEdge(node, edgeType);
		}
	private:
		ChainBuilder& chain;
		EdgeType edgeType;
	} nodeFromEgde;

	ChainNodeBuilder* operator->() {
		return &nodeFromEgde;
	}

private:
	ChainBuilder& addDstNodeOnEdge(const Node& node, EdgeType type) {
		graph.addNode(node);
		if (lastNode) {
			graph.addEdge(Edge(type, *lastNode, node));
		}
		lastNode = const_cast<Node*>(&node);
		return *this;
	}

private:
	Node* lastNode{nullptr};
	Graph& graph;
};

int main() {
	Graph g("graph");

	Node a("a");
	Node b("b");
	Node c("c");
	Node d("d");
	Node e("e");

	ChainBuilder(g) -> NODE(a) -> NODE(b) -> NODE(c) -> NODE(d) -> NODE(e);
	ChainBuilder(g, CTRL_EDGE) -> NODE(a) -> NODE(c);

	return GraphLayout::layout(g);
}
