#include "easy_graph/modifier/revises/edge_adder.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/infra/status.h"

EG_NS_BEGIN

EdgeAdder::EdgeAdder(const Edge& edge)
: edge(edge){
}

Status EdgeAdder::execute(Graph& graph) const {
	if (graph.findEdge(edge)) return Status::FAILURE;
	graph.addEdge(std::move(edge));
	return Status::SUCCESS;
}

EG_NS_END
