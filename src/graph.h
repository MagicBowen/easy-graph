#ifndef H813EC8C1_3850_4320_8AC0_CE071C89B871
#define H813EC8C1_3850_4320_8AC0_CE071C89B871

#include "easy_graph/eg.h"
#include <string>
#include <set>
#include "node.h"
#include "edge.h"

EG_NS_BEGIN

struct Node;
struct Edge;
struct NodeVisitor;
struct EdgeVisitor;

struct Graph {
	Graph(const std::string name);

	void addNode(const Node&);
	void addEdge(const Edge&);

	void accept(NodeVisitor&) const;
	void accept(EdgeVisitor&) const;

private:
	std::string name;
	std::set<Node> nodes;
	std::set<Edge> edges;
};

EG_NS_END

#endif
