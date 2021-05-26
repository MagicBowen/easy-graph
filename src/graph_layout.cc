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

	Status GraphEasyLayoutInShell(const std::string& graph_str) {
		std::string script =  std::string("echo \"") + graph_str + std::string("\"|graph-easy");
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

	return GraphEasyLayoutInShell(layout);
}

EG_NS_END
