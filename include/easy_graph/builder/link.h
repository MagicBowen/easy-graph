#ifndef H35695B82_E9E5_419D_A6B4_C13FB0842C9F
#define H35695B82_E9E5_419D_A6B4_C13FB0842C9F

#include "easy_graph/graph/edge_type.h"
#include "easy_graph/graph/port_id.h"
#include "easy_graph/graph/attributes.h"
#include <string>

EG_NS_BEGIN

struct Link {
	explicit Link(EdgeType type) : type(type) {
		reset(type);
	}

	void setPortId(PortId id) {
		if (srcPortId == UNDEFINED_PORT_ID) {
			srcPortId = id;
		} else {
			dstPortId = id;
		}
	}

	void reset(EdgeType type) {
		this->type = type;
		this->srcPortId = UNDEFINED_PORT_ID;
		this->dstPortId = UNDEFINED_PORT_ID;
		this->attrs.clear();
	}

	EdgeType type;
	PortId srcPortId{UNDEFINED_PORT_ID};
	PortId dstPortId{UNDEFINED_PORT_ID};
	Attributes attrs;
};

EG_NS_END

#endif
