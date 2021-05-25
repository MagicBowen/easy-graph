#include "graph_layout.h"
#include <string>
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "shell_executor.h"
#include "node_visitor.h"
#include "edge_visitor.h"
#include "layout_option.h"

EG_NS_BEGIN

namespace {
	LayoutOption globalLayoutOptions;

	Status GraphEasyLayoutInShell(const std::string& graph_str) {
		std::string script =  std::string("echo \"") + graph_str + std::string("\"|graph-easy");
		return ShellExecutor::execute(script);
	}

	template<typename VISITOR, typename ITEM>
	struct GraphItemVisitor : VISITOR {
		GraphItemVisitor(const LayoutOption& options)
		: options(options) {
		}

		OVERRIDE(void visit(const ITEM& item)) {
			const Layoutable& layoutable = item;
			layout += layoutable.getLayout(options);
		}

		std::string layout;
		const LayoutOption& options;
	};
}

void GraphLayout::config(const LayoutOption& options) {
	globalLayoutOptions = options;
}

Status GraphLayout::layout(const Graph& graph, const LayoutOption* opts) {
	const LayoutOption& options = opts ? *opts : globalLayoutOptions;

	GraphItemVisitor<NodeVisitor, Node> nodeLayoutVisitor(options);
	graph.accept(nodeLayoutVisitor);

	GraphItemVisitor<EdgeVisitor, Edge> edgeLayoutVisitor(options);
	graph.accept(edgeLayoutVisitor);

	std::string layout = ((Layoutable&)graph).getLayout(options)
			           + nodeLayoutVisitor.layout
					   + edgeLayoutVisitor.layout;

	return GraphEasyLayoutInShell(layout);
}

EG_NS_END
