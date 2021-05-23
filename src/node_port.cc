#include "node_port.h"
#include "node.h"

EG_NS_BEGIN

NodePort::NodePort(const Node& node, PortId portId)
: node(node), portId(portId){
}

__DEF_EQUALS(NodePort)
{
	return  (node.getId() == rhs.node.getId()) && (portId == rhs.portId);
}

__DEF_COMP(NodePort)
{
	if (node.getId() < rhs.node.getId()) return true;
	if ((node.getId() == rhs.node.getId()) && (portId < rhs.portId)) return true;
	return false;
}

EG_NS_END
