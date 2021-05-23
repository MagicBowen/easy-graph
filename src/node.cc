#include "node.h"

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

std::string Node::getLayout() const {
	return std::string("[") + id + std::string("]");
}

EG_NS_END
