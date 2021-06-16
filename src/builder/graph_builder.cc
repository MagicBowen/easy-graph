#include "easy_graph/builder/graph_builder.h"
#include "easy_graph/builder/port_aware_trait.h"
#include "easy_graph/infra/trait_cast.h"
#include "easy_graph/graph/edge_type.h"
#include "easy_graph/graph/endpoint.h"
#include "easy_graph/builder/link.h"
#include "easy_graph/infra/log.h"

EG_NS_BEGIN

namespace {
	PortId getPortIdBy(const EdgeType& type, const PortId& specifiedPortId, PortId& reservedPortId) {
		if (!trait_cast<PortAwareTrait>(type)) return 0;
		if (specifiedPortId == UNDEFINED_PORT_ID) return reservedPortId++;
		if (specifiedPortId < reservedPortId) return specifiedPortId;
		reservedPortId = specifiedPortId;
		return reservedPortId++;
	}
}

GraphBuilder::GraphBuilder(const std::string& name)
: graph(name) {
}

GraphBuilder::NodeInfo* GraphBuilder::findNode(const NodeId& id) {
	auto it = nodes.find(id);
	if (it == nodes.end()) {
		return nullptr;
	}
	return &(it->second);
}

const GraphBuilder::NodeInfo* GraphBuilder::findNode(const NodeId& id) const {
	return const_cast<GraphBuilder&>(*this).findNode(id);
}

Edge* GraphBuilder::buildEdge(const Node& src, const Node& dst, Link& link) {
	NodeInfo* srcInfo = findNode(src.getId());
	NodeInfo* dstInfo = findNode(dst.getId());

	if(!srcInfo || !dstInfo) {
		EG_ERR("link edge{endpoint : (&s , %s) , type : %s} error!", src.getId().c_str(), dst.getId().c_str(), typeid(*link.type).name());
		return nullptr;
	}

	PortId srcPortId = getPortIdBy(*link.type, link.srcPortId, srcInfo->outPortMax);
	PortId dstPortId = getPortIdBy(*link.type, link.dstPortId, dstInfo->inPortMax);

	EG_DBG("link edge(%s) from (%s:%d) to (%s:%d)", typeid(*link.type).name(), src.getId().c_str(), srcPortId, dst.getId().c_str(), dstPortId);

	Edge edge(*link.type, Endpoint(src.getId(), srcPortId), Endpoint(dst.getId(), dstPortId));
	edge.replaceAttrs(std::move(link.attrs));
	return graph.addEdge(std::move(edge));
}

EG_NS_END
