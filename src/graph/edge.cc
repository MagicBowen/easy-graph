#include "easy_graph/graph/edge.h"

EG_NS_BEGIN

Edge::Edge(const EdgeType type,
		   const std::string& label,
		   const Endpoint& src,
		   const Endpoint& dst)
: type(type), label(label), src(src),dst(dst) {
}

__DEF_EQUALS(Edge)
{
	return  (type == rhs.type) && (src == rhs.src) && (dst == rhs.dst);
}

__DEF_COMP(Edge)
{
	if (src < rhs.src) return true;
	if ((src == rhs.src) && (dst < rhs.dst)) return true;
	if ((src == rhs.src) && (dst < rhs.dst) && (type < rhs.type)) return true;
	return false;
}

EdgeType Edge::getType() const {
	return type;
}

std::string Edge::getLabel() const {
	return label;
}

Endpoint Edge::getSrc() const {
	return src;
}
Endpoint Edge::getDst() const {
	return dst;
}

EG_NS_END
