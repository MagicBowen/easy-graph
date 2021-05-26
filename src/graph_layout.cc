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

	std::string getLayoutFormat(const LayoutOption& option) {
		switch(option.format) {
		case LayoutFormat::ASCII: return "ascii";
		case LayoutFormat::BOXART: return "boxart";
		case LayoutFormat::SVG: return "svg";
		case LayoutFormat::DOT: return "dot";
		case LayoutFormat::HTML: return "html";
		}
		return "ascii";
	}

	std::string getLayoutFilePostfix(const LayoutOption& option) {
		switch(option.format) {
		case LayoutFormat::ASCII: return "txt";
		case LayoutFormat::BOXART: return "txt";
		case LayoutFormat::SVG: return "svg";
		case LayoutFormat::DOT: return "dot";
		case LayoutFormat::HTML: return "html";
		}
		return "txt";
	}

	std::string getLayoutOutput(const LayoutOption& options, const std::string& graphName) {
		if (options.output == LayoutOutput::CONSOLE) return "";
		return std::string(" --output ") + options.outputPath + graphName + "." + getLayoutFilePostfix(options);

	}

	Status GraphEasyLayoutInShell(const std::string& graphName, const std::string& graphEasyText, const LayoutOption& options) {
		std::string script =  std::string("echo \"") + graphEasyText + "\"|graph-easy --as=" + getLayoutFormat(options) + getLayoutOutput(options, graphName);
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
