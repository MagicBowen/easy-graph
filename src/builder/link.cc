#include "easy_graph/builder/link.h"

EG_NS_BEGIN

Link::Link(const EdgeType& type) : type(&type) {
}

void Link::setPorts(const PortPair& pp) {
	srcPortId = pp.first;
	dstPortId = pp.second;
}

void Link::setPort(const PortId& id) {
	if (srcPortId == UNDEFINED_PORT_ID) {
		srcPortId = id;
		return;
	}
	if (dstPortId == UNDEFINED_PORT_ID) {
		dstPortId = id;
	}
}

EG_NS_END
