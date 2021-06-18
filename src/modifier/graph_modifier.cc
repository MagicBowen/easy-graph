#include "easy_graph/modifier/graph_modifier.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/infra/status.h"
#include "easy_graph/infra/log.h"

EG_NS_BEGIN

GraphModifier::GraphModifier(Graph& graph)
: graph(graph) {
}

Status GraphModifier::commit(bool atom) {
	auto backup = atom ? graph : Graph("");
	auto ret = doCommit(atom);
	if (eg_status_failed(ret)) {
		graph = std::move(backup);
	}
	return ret;
}

Status GraphModifier::doCommit(bool atom) {
	for (const auto& revise : revises) {
		if (eg_status_failed(revise->execute(graph))) {
			EG_WARN("graph modifier commit error!");
			if (atom) return Status::FAILURE;
		}
	}
	return Status::SUCCESS;
}

void GraphModifier::clear() {
	revises.clear();
}


EG_NS_END
