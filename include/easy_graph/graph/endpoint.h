#ifndef H8DB48A37_3257_4E15_8869_09E58221ADE8
#define H8DB48A37_3257_4E15_8869_09E58221ADE8

#include "easy_graph/graph/node_id.h"
#include "easy_graph/graph/port_id.h"
#include "easy_graph/infra/operator.h"

EG_NS_BEGIN

struct Endpoint {
	Endpoint(const NodeId&, const PortId&);

	__DECL_COMP(Endpoint);

	NodeId getNodeId() const;
	PortId getPortId() const;

private:
	NodeId nodeId;
	PortId portId;
};

EG_NS_END

#endif
