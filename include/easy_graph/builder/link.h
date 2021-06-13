#ifndef H35695B82_E9E5_419D_A6B4_C13FB0842C9F
#define H35695B82_E9E5_419D_A6B4_C13FB0842C9F

#include "easy_graph/graph/port_id.h"
#include "easy_graph/graph/attributes.h"
#include <string>

EG_NS_BEGIN

struct EdgeType;

struct Link {
	explicit Link(const EdgeType& type);
	void setPortId(PortId id);
	void reset(const EdgeType& type);

	EdgeType* type{nullptr};
	PortId srcPortId{UNDEFINED_PORT_ID};
	PortId dstPortId{UNDEFINED_PORT_ID};
	Attributes attrs;
};

EG_NS_END

#endif
