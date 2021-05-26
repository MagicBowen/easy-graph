#include "graph_layout.h"
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "shell_executor.h"
#include "node_visitor.h"
#include "edge_visitor.h"
#include "layout_option.h"
#include "layout_visitor.h"
#include "layout_context.h"

EG_NS_BEGIN

namespace {
	LayoutOption globalLayoutOptions;

	Status GraphEasyLayoutInShell(const std::string& graphName, const std::string& graphEasyText, const LayoutOption& options) {
		std::string script =  std::string("echo \"") + graphEasyText + "\"|graph-easy " + options.getLayoutCmdArgs(graphName);
		return ShellExecutor::execute(script);
	}
}

void GraphLayout::config(const LayoutOption& options) {
	globalLayoutOptions = options;
}

Status GraphLayout::layout(const Graph& graph, const LayoutOption* opts) {
	const LayoutOption options = opts ? *opts : globalLayoutOptions;

	LayoutContext context(graph.getName(), options);

	LayoutVisitor<NodeVisitor, Node> nodeLayoutVisitor(context);
	graph.accept(nodeLayoutVisitor);

	LayoutVisitor<EdgeVisitor, Edge> edgeLayoutVisitor(context);
	graph.accept(edgeLayoutVisitor);

	std::string layout = ((Layoutable&)graph).getLayout(context)
			           + nodeLayoutVisitor.layout
					   + edgeLayoutVisitor.layout;

	return GraphEasyLayoutInShell(graph.getName(), layout, options);
}

EG_NS_END
