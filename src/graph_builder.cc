#include "graph_builder.h"

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

EG_NS_END
