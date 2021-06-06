#include "easy_graph/builder/graph_builder.h"
#include "easy_graph/builder/link.h"
#include "easy_graph/infra/log.h"

EG_NS_BEGIN

namespace {
	PortId getPortIdBy(const EdgeType& type, const PortId& specifiedPortId, PortId& reservedPortId) {
		if (type == EdgeType::CTRL) return 0;
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

Node* GraphBuilder::buildNode(const Node& node) {
	auto it = nodes.find(node.getId());
	if (it == nodes.end()) {
		nodes.emplace(std::make_pair(node.getId(), NodeInfo()));
	}
	return graph.addNode(node);
}

Edge* GraphBuilder::buildEdge(const Node& src, const Node& dst, const Link& link) {
	NodeInfo* srcInfo = findNode(src.getId());
	NodeInfo* dstInfo = findNode(dst.getId());

	if(!srcInfo || !dstInfo) {
		EG_ERR("link edge{%d : %s} error!", link.type, link.label.c_str());
		return nullptr;
	}

	PortId srcPortId = getPortIdBy(link.type, link.srcPortId, srcInfo->outPortMax);
	PortId dstPortId = getPortIdBy(link.type, link.dstPortId, dstInfo->inPortMax);

	EG_DBG("link edge(%d) from (%s:%d) to (%s:%d)", link.type, src.getId().c_str(), srcPortId, dst.getId().c_str(), dstPortId);

	return graph.addEdge(Edge(link.type, link.label, NodePort(src, srcPortId), NodePort(dst, dstPortId)));
}

EG_NS_END
