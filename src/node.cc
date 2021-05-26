#include "node.h"
#include "graph.h"
#include "layout_visitor.h"
#include "node_visitor.h"

EG_NS_BEGIN

Node::Node(const NodeId& id)
: id(id) {
}

Node::Node(const char* id)
: Node(NodeId(id)) {
}

__DEF_EQUALS(Node)
{
	return id == rhs.id;
}

__DEF_COMP(Node)
{
	return id < rhs.id;
}

NodeId Node::getId() const {
	return id;
}

std::string Node::getLayout(const LayoutOption& options) const {
	if (subgraphs.empty()) return std::string("[") + id + "]";

	std::string layout = std::string("( ") + id + " : [" + id + "]";
	std::for_each(subgraphs.begin(), subgraphs.end(), [&layout, &options](auto& g) {
		LayoutVisitor<NodeVisitor, Node> nodeLayoutVisitor(options);
		g->accept(nodeLayoutVisitor);
		layout += nodeLayoutVisitor.layout;
	});
	return layout + ")";
}

EG_NS_END
