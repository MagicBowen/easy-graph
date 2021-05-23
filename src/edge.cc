#include "edge.h"
#include "node.h"

EG_NS_BEGIN

Edge::Edge(const EdgeType type, const std::string& label, const Node& src, const Node& dst)
: type(type), label(label), src(src), dst(dst) {
}

__DEF_EQUALS(Edge)
{
	return (type == rhs.type) && (label == rhs.label) && (src == rhs.src) && (dst == rhs.dst);
}

__DEF_COMP(Edge)
{
	if (src < rhs.src) return true;
	if (dst < rhs.dst) return true;
	if (label < rhs.label) return true;
	if (type < rhs.type) return true;
	return false;
}

std::string Edge::getLayout() const {
	std::string arrow = (type == DATA_EDGE) ? "-->" : "..>";
	std::string labelLayout = (label == "") ? "" : (std::string("{label : ") + label + "}");
	return src.getLayout() + arrow + labelLayout + dst.getLayout();
}

EG_NS_END
