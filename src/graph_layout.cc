#include "graph_layout.h"
#include "layout_executor.h"
#include "graph.h"

EG_NS_BEGIN

void GraphLayout::config(layoutExecutor& executor, const LayoutOption* opts) {
	this->executor = &executor;
	options = opts;
}

Status GraphLayout::layout(const Graph& graph, const LayoutOption* opts) {
	const LayoutOption* options = opts ? opts : this->options;
	if (!executor) return EG_UNIMPLEMENTED;
	return executor->layout(graph, options);
}

EG_NS_END
