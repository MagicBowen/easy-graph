#include "easy_graph/graph/node_port.h"
#include "easy_graph/graph/node.h"

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

const Node& NodePort::getNode() const {
	return node;
}

PortId NodePort::getPortId() const {
	return portId;
}

EG_NS_END
