#include "easy_graph/modifier/revises/edge_eraser.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/infra/status.h"

EG_NS_BEGIN

EdgeEraser::EdgeEraser(const Edge& edge)
: edge(edge){
}

Status EdgeEraser::execute(Graph& graph) const {
	if (!graph.findEdge(edge)) return Status::FAILURE;
	graph.remove(edge);
	return Status::SUCCESS;
}


EG_NS_END
