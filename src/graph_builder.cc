#include "graph_builder.h"
#include "log.h"

EG_NS_BEGIN

GraphBuilder::GraphBuilder(const std::string& name)
: graph(name) {
}

Graph& GraphBuilder::getGraph() {
	return this->graph;
}

const Graph& GraphBuilder::getGraph() const {
	return this->graph;
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

Node* GraphBuilder::addNode(const Node& node) {
	nodes.emplace(std::make_pair(node.getId(), NodeInfo()));
	return graph.addNode(node);
}

void GraphBuilder::addEdge(EdgeType type, const std::string& label, Node& src, Node& dst) {
	NodeInfo* srcInfo = findNode(src.getId());
	NodeInfo* dstInfo = findNode(dst.getId());
	if(!srcInfo || !dstInfo) {
		EG_ERR("link edge{%d : %s} error!", type, label.c_str());
		return;
	}
	return graph.addEdge(Edge(type, label, NodePort(src, srcInfo->jointOutNum++), NodePort(dst, srcInfo->jointInNum++)));
}

EG_NS_END
