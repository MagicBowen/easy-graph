#include "graph_layout.h"
#include "log.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <sys/wait.h>
#include <sys/types.h>
#include "graph.h"
#include "node_visitor.h"
#include "edge_visitor.h"
#include "node.h"
#include "edge.h"


EG_NS_BEGIN

namespace {
	Status OsSystemExec(const char* script) {
		pid_t status = system(script);
		if (-1 == status)
		{
			EG_ERR("system execute return error!");
			return EG_FAILURE;
		}

		if (WIFEXITED(status) &&  (0 == WEXITSTATUS(status))) return EG_SUCCESS;

		EG_ERR("system execute {%s} exit status value = [0x%x], exit code: %d\n", script, status, WEXITSTATUS(status));
		return EG_FAILURE;
	}

	Status SystemGraphEasyLayout(const std::string& graph_str) {
		std::ostringstream script;
		script << "echo \"" << graph_str << "\"|graph-easy";
		return OsSystemExec(script.str().c_str());
	}

	std::string getNodeLayout(const Node& node) {
		return std::string("[") + node.getName() + std::string("]");
	}

	std::string getEdgeLayout(const Edge& edge) {
		return getNodeLayout(edge.getSrcNode()) + std::string("-->") + getNodeLayout(edge.getDstNode());
	}

	struct NodeLayoutVisitor : NodeVisitor {
		std::string layout;

		OVERRIDE(void visit(const Node& node)) {
			layout += getNodeLayout(node);
		}
	};

	struct EdgeLayoutVisitor : EdgeVisitor {
		std::string layout;

		OVERRIDE(void visit(const Edge& edge)) {
			layout += getEdgeLayout(edge);
		}
	};
}

GraphLayout::GraphLayout(const Graph& graph)
: graph(graph) {
}

Status GraphLayout::layout() const {
	NodeLayoutVisitor nodeLayoutVisitor;
	EdgeLayoutVisitor edgeLayoutVisitor;
	graph.accept(nodeLayoutVisitor);
	graph.accept(edgeLayoutVisitor);
	SystemGraphEasyLayout(nodeLayoutVisitor.layout + edgeLayoutVisitor.layout);
	return EG_SUCCESS;
}

EG_NS_END
