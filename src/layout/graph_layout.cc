#include "easy_graph/layout/graph_layout.h"
#include "easy_graph/layout/layout_engine.h"
#include "easy_graph/graph/graph.h"

EG_NS_BEGIN

void GraphLayout::config(LayoutEngine& executor, const LayoutOption* opts) {
	this->executor = &executor;
	options = opts;
}

Status GraphLayout::layout(const Graph& graph, const LayoutOption* opts) {
	const LayoutOption* options = opts ? opts : this->options;
	if (!executor) return EG_UNIMPLEMENTED;
	return executor->layout(graph, options);
}

EG_NS_END
