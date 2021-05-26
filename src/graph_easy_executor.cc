#include "graph_easy_executor.h"
#include "graph_easy_visitor.h"
#include "graph_easy_option.h"
#include "layout_option.h"
#include "shell_executor.h"
#include "graph.h"

EG_NS_BEGIN

namespace {
	const GraphEasyOption* graphEasyOptionCast(const LayoutOption* opts) {
		if (!opts) return &(GraphEasyOption::getDefault());
		auto options = dynamic_cast<const GraphEasyOption*>(opts);
		if (options) return options;
		return &(GraphEasyOption::getDefault());
	}
}

Status GraphEasyExecutor::layout(const Graph& graph, const LayoutOption* opts) {

	auto options = graphEasyOptionCast(opts);

	GraphEasyVisitor visitor(*options);
	graph.accept(visitor);

	std::string script =  std::string("echo \"") + visitor.getLayout() + "\"|graph-easy " + options->getLayoutCmdArgs(graph.getName());
	return ShellExecutor::execute(script);
}

EG_NS_END
