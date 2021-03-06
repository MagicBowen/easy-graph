#include "easy_graph/layout/engines/graph_easy/graph_easy_layout_engine.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_visitor.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "layout/engines/graph_easy/utils/shell_executor.h"
#include "easy_graph/layout/layout_option.h"
#include "easy_graph/graph/graph.h"

EG_NS_BEGIN

namespace {
	const GraphEasyOption* graphEasyOptionCast(const LayoutOption* opts) {
		if (!opts) return &(GraphEasyOption::getDefault());
		auto options = dynamic_cast<const GraphEasyOption*>(opts);
		if (options) return options;
		return &(GraphEasyOption::getDefault());
	}
}

Status GraphEasyLayoutEngine::layout(const Graph& graph, const LayoutOption* opts) {
	auto options = graphEasyOptionCast(opts);
	GraphEasyVisitor visitor(*options);
	graph.accept(visitor);

	std::string script = std::string("echo \"")
			           + visitor.getLayout()
					   + "\" | graph-easy "
					   + options->getLayoutCmdArgs(graph.getName());
	return ShellExecutor::execute(script);
}

EG_NS_END
