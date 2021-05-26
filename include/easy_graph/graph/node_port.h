#ifndef HDD542CAC_AE33_4C33_B6A3_602F5D147DAE
#define HDD542CAC_AE33_4C33_B6A3_602F5D147DAE

#include "easy_graph/graph/port_id.h"
#include "easy_graph/infra/cmp_helper.h"

EG_NS_BEGIN

struct Node;

struct NodePort {
	NodePort(const Node& node, PortId portId);

	__DECL_COMP(NodePort);

	const Node& getNode() const;
	PortId getPortId() const;

private:
	const Node& node;
	PortId portId;
};

EG_NS_END

#endif
