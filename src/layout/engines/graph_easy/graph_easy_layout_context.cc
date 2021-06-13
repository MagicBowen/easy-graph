#include "easy_graph/layout/engines/graph_easy/graph_easy_layout_context.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "easy_graph/graph/graph.h"

EG_NS_BEGIN

GraphEasyLayoutContext::GraphEasyLayoutContext(const GraphEasyOption& options)
: options(options){
}

const Graph* GraphEasyLayoutContext::getCurrentGraph() const {
	if (graphs.empty()) return nullptr;
	return graphs.back();
}

void GraphEasyLayoutContext::enterGraph(const Graph& graph) {
	graphs.push_back(&graph);
}

void GraphEasyLayoutContext::exitGraph() {
	graphs.pop_back();
}

std::string GraphEasyLayoutContext::getGroupPath() const {
	if (graphs.empty()) return "";
	std::string result("");
	std::for_each(graphs.begin(), graphs.end(), [&result](const auto& graph) {
		result += (std::string("/") + graph->getName());
	});
	return (result + "/");
}

const GraphEasyOption& GraphEasyLayoutContext::getOptions() const {
	return options;
}

EG_NS_END
