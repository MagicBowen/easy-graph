#include "easy_graph/modifier/graph_modifier.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/infra/status.h"

EG_NS_BEGIN

GraphModifier::GraphModifier(Graph& graph)
: graph(graph) {
}

Status GraphModifier::commit() {
	Graph original = graph;
	auto executor = [this](const auto &revise) { return revise.execute(graph); };
	for (const auto& revise : revises) {
		if (eg_status_failed(std::visit(executor, revise))) {
			graph = std::move(original);
			return Status::FAILURE;
		}
	}
	return Status::SUCCESS;
}

void GraphModifier::clear() {
	revises.clear();
}


EG_NS_END
