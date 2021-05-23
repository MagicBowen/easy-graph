#include "graph_layout.h"
#include <string>
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "shell_executor.h"
#include "node_visitor.h"
#include "edge_visitor.h"

EG_NS_BEGIN

namespace {
	Status GraphEasyLayoutInShell(const std::string& graph_str) {
		std::string script =  std::string("echo \"") + graph_str + std::string("\"|graph-easy");
		return ShellExecutor::execute(script);
	}

	std::string getGraphTitle (const std::string graphName, FlowDirection direction) {
		std::string flow_layout = (direction == FLOW_LR) ? "east" : "down";
		return std::string("graph { label : ") + graphName +  "; flow : " + flow_layout + " } \n";
	}

	struct NodeLayoutVisitor : NodeVisitor {
		OVERRIDE(void visit(const Node& node)) {
			layout += node.getLayout();
		}

		std::string layout;
	};

	struct EdgeLayoutVisitor : EdgeVisitor {
		OVERRIDE(void visit(const Edge& edge)) {
			layout += edge.getLayout();
		}

		std::string layout;
	};
}

Status GraphLayout::layout(const Graph& graph, FlowDirection direction) {
	NodeLayoutVisitor nodeLayoutVisitor;
	graph.accept(nodeLayoutVisitor);

	EdgeLayoutVisitor edgeLayoutVisitor;
	graph.accept(edgeLayoutVisitor);

	std::string layout = getGraphTitle(graph.getName(), direction)
			           + nodeLayoutVisitor.layout
					   + edgeLayoutVisitor.layout;

	return GraphEasyLayoutInShell(layout);
}

EG_NS_END
