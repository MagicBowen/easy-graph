#ifndef H813EC8C1_3850_4320_8AC0_CE071C89B871
#define H813EC8C1_3850_4320_8AC0_CE071C89B871

#include "flow_direction.h"
#include "node.h"
#include "edge.h"
#include <string>
#include <set>
#include <map>

EG_NS_BEGIN

struct NodeVisitor;
struct EdgeVisitor;

struct Graph {
	explicit Graph(const std::string& name);

	std::string getName() const;

	Node* addNode(const Node&);
	void addEdge(const Edge&);

	Node* findNode(const NodeId&);
	const Node* findNode(const NodeId&) const;

	void accept(NodeVisitor&) const;
	void accept(EdgeVisitor&) const;

	void layout(FlowDirection dir = FLOW_LR) const;

private:
	std::string name;
	std::map<NodeId, Node> nodes;
	std::set<Edge> edges;
};

EG_NS_END

#endif
