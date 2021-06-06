#include "easy_graph/graph/endpoint.h"

EG_NS_BEGIN

Endpoint::Endpoint(const NodeId& nodeId, const PortId& portId)
: nodeId(nodeId), portId(portId) {
}

__DEF_EQUALS(Endpoint)
{
	return  (nodeId == rhs.nodeId) && (portId == rhs.portId);
}

__DEF_COMP(Endpoint)
{
	if (nodeId < rhs.nodeId) return true;
	if ((nodeId == rhs.nodeId) && (portId < rhs.portId)) return true;
	return false;
}

NodeId Endpoint::getNodeId() const {
	return nodeId;
}

PortId Endpoint::getPortId() const {
	return portId;
}

EG_NS_END
