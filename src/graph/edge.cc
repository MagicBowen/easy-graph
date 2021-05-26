#include "easy_graph/graph/edge.h"
#include "easy_graph/graph/node.h"

EG_NS_BEGIN

Edge::Edge(const EdgeType type,
		   const std::string& label,
		   const NodePort& src,
		   const NodePort& dst)
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

const NodePort& Edge::getSrc() const {
	return src;
}

const NodePort& Edge::getDst() const {
	return dst;
}

EG_NS_END
