#include "edge.h"
#include "node.h"

EG_NS_BEGIN

Edge::Edge(const EdgeType type, const Node& src, const Node& dst)
: type(type), src(src), dst(dst) {
}

__DEF_EQUALS(Edge)
{
	return (type == rhs.type) && (src == rhs.src) && (dst == rhs.dst);
}

__DEF_COMP(Edge)
{
	if (src < rhs.src) return true;
	if (dst < rhs.dst) return true;
	if (type < rhs.type) return true;
	return false;
}

EdgeType Edge::getType() const {
	return type;
}

const Node& Edge::getSrcNode() const {
	return src;
}

const Node& Edge::getDstNode() const {
	return dst;
}

EG_NS_END
