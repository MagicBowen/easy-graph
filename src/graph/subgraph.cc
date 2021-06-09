#include "easy_graph/graph/subgraph.h"
#include "easy_graph/graph/graph.h"

EG_NS_BEGIN

Subgraph::Subgraph(const Graph& graph)
: name(graph.getName()), graph(graph){
}

Subgraph::Subgraph(const std::string& name, const Graph& graph)
: name(name), graph(graph) {
}

__DEF_EQUALS(Subgraph) {
	return this->graph == rhs.graph;
}

std::string Subgraph::getName() const {
	return name;
}

const Graph& Subgraph::getGraph() const {
	return graph;
}


EG_NS_END
