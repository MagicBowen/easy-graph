#include "easy_graph/modifier/revises/node_adder.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/infra/status.h"

EG_NS_BEGIN

NodeAdder::NodeAdder(Node node)
: node(std::move(node)) {
}

Status NodeAdder::execute(Graph& graph) const {
	if (graph.findNode(node.getId())) return Status::FAILURE;
	graph.addNode(std::move(node));
	return Status::SUCCESS;
}

EG_NS_END
