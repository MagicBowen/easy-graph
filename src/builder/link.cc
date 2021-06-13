#include "easy_graph/builder/link.h"

EG_NS_BEGIN

Link::Link(const EdgeType& type) {
	reset(type);
}

void Link::setPortId(PortId id) {
	if (srcPortId == UNDEFINED_PORT_ID) {
		srcPortId = id;
	} else {
		dstPortId = id;
	}
}

void Link::reset(const EdgeType& type) {
	this->type = const_cast<EdgeType*>(&type);
	this->srcPortId = UNDEFINED_PORT_ID;
	this->dstPortId = UNDEFINED_PORT_ID;
	this->attrs.clear();
}

EG_NS_END
