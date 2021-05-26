#include "node.h"
#include "graph.h"
#include "layout_visitor.h"
#include "node_visitor.h"
#include "layout_context.h"

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

std::string Node::getLayout(LayoutContext& context) const {
	std::string nodeBox = std::string("[") + id + "]";

	if (subgraphs.empty()) return nodeBox;
	if (context.inLinking()) return nodeBox;

	std::string layout = std::string("( ") + id + ": " + nodeBox;
	std::for_each(subgraphs.begin(), subgraphs.end(), [&](auto& g) {
		layout += (std::string(" -- [") + id + "/" + g->getName() + "]" + "{class : subgraph} ");
	});
	return layout + ")";
}

EG_NS_END
