#include "easy_graph/graph/edge.h"

EG_NS_BEGIN

Edge::Edge(const EdgeType& type,
		   const Endpoint& src,
		   const Endpoint& dst)
: type(type), src(src),dst(dst) {
}

__DEF_EQUALS(Edge)
{
	return  (src == rhs.src) && (dst == rhs.dst) && (type == rhs.type);
}

__DEF_COMP(Edge)
{
	if (src < rhs.src) return true;
	if ((src == rhs.src) && (dst < rhs.dst)) return true;
	if ((src == rhs.src) && (dst < rhs.dst) && (type < rhs.type)) return true;
	return false;
}

const EdgeType& Edge::getType() const {
	return type;
}

Endpoint Edge::getSrc() const {
	return src;
}
Endpoint Edge::getDst() const {
	return dst;
}

EG_NS_END
