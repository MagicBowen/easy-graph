#ifndef H35695B82_E9E5_419D_A6B4_C13FB0842C9F
#define H35695B82_E9E5_419D_A6B4_C13FB0842C9F

#include "edge_type.h"
#include "port_id.h"
#include <string>

EG_NS_BEGIN

struct Link {
	explicit Link(EdgeType type) : type(type) {
		reset(type);
	}

	Link(EdgeType type, const std::string& label, PortId srcPortId, PortId dstPortId)
	: type(type), label(label), srcPortId(srcPortId), dstPortId(dstPortId){
	}

	void reset(EdgeType type) {
		this->type = type;
		this->label = "";
		this->srcPortId = UNDEFINED_PORT_ID;
		this->dstPortId = UNDEFINED_PORT_ID;
	}

	EdgeType type;
	std::string label;
	PortId srcPortId;
	PortId dstPortId;
};

EG_NS_END

#endif
