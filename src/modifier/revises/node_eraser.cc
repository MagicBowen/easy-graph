#include "easy_graph/modifier/revises/node_eraser.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/infra/status.h"

EG_NS_BEGIN

NodeEraser::NodeEraser(const NodeId& id)
: id(id) {
}

Status NodeEraser::execute(Graph& graph) const {
	auto node = graph.findNode(id);
	if (!node) return Status::FAILURE;
	graph.remove(id);
	return Status::SUCCESS;
}

EG_NS_END
