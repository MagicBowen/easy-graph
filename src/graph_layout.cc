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

	struct NodeLayoutVisitor : NodeVisitor {
		std::string layout;

		OVERRIDE(void visit(const Node& node)) {
			layout += node.getLayout();
		}
	};

	struct EdgeLayoutVisitor : EdgeVisitor {
		std::string layout;

		OVERRIDE(void visit(const Edge& edge)) {
			layout += edge.getLayout();
		}
	};
}

Status GraphLayout::layout(const Graph& graph) {
	NodeLayoutVisitor nodeLayoutVisitor;
	EdgeLayoutVisitor edgeLayoutVisitor;
	graph.accept(nodeLayoutVisitor);
	graph.accept(edgeLayoutVisitor);
	return GraphEasyLayoutInShell(nodeLayoutVisitor.layout + edgeLayoutVisitor.layout);
}

EG_NS_END
