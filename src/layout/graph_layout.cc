#include "easy_graph/layout/graph_layout.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_layout_engine.h"

EG_NS_BEGIN

namespace {
	GraphEasyLayoutEngine defaultExecutor;
}

void GraphLayout::config(LayoutEngine& executor, const LayoutOption* opts) {
	this->executor = &executor;
	options = opts;
}

void GraphLayout::reset() {
	this->executor = nullptr;
	this->options = nullptr;
}

Status GraphLayout::layout(const Graph& graph, const LayoutOption* opts) {
	const LayoutOption* options = opts ? opts : this->options;
	if (!executor) return static_cast<LayoutEngine&>(defaultExecutor).layout(graph, options);
	return executor->layout(graph, options);
}

EG_NS_END
