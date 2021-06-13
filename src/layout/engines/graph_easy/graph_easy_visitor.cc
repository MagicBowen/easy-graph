#include "easy_graph/layout/engines/graph_easy/graph_easy_visitor.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_edge_layout_trait.h"
#include "easy_graph/graph/subgraph_visitor.h"
#include "easy_graph/infra/scope_guard.h"
#include "easy_graph/infra/trait_cast.h"
#include "easy_graph/graph/edge_type.h"
#include "easy_graph/graph/subgraph.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/graph/edge.h"
#include "easy_graph/graph/node.h"
#include "easy_graph/infra/log.h"

EG_NS_BEGIN

namespace {
	struct SubgraphLayoutVisitor : SubgraphVisitor {
		SubgraphLayoutVisitor(const NodeId& id, GraphEasyLayoutContext& ctxt)
		: id(id), ctxt(ctxt) {
		}
		std::string layout;

	private:
		void visit(const Subgraph& subgraph) override {
			ScopeGuard guard([this, &subgraph](){ctxt.enterGraph(subgraph.getGraph());}, [this](){ctxt.exitGraph();});
			layout += (std::string(" -- [") + id + "/" + subgraph.getName() + "]" + "{class : subgraph; label : " + subgraph.getName() + ";}");
		}
	private:
		NodeId id;
		GraphEasyLayoutContext& ctxt;
	};

	/////////////////////////////////////////////////////////////////////////
	std::string getGraphLayoutTitle(const Graph& graph, const GraphEasyLayoutContext& ctxt) {
		std::string flowDirection = (ctxt.getOptions().dir == FlowDir::LR) ? "east" : "down";
		std::string graphTitle = std::string("graph { label : ")
				               + graph.getName()
							   +  "; flow : "
							   + flowDirection + " ; } node.subgraph { border : double-dash; }";
		return graphTitle;
	}
	/////////////////////////////////////////////////////////////////////////
	std::string getNodeBaseLayout(const Node& node) {
		return std::string("[") + node.getId() + "]";
	}

	/////////////////////////////////////////////////////////////////////////
	std::string getNodeLayout(const Node& node, GraphEasyLayoutContext& ctxt) {
		auto id = node.getId();
		std::string nodeLayout = getNodeBaseLayout(node);

		if (!node.hasSubgraph()) return nodeLayout;

		SubgraphLayoutVisitor subgraphVisitor(id, ctxt);
		node.accept(subgraphVisitor);
		return (std::string("( ") + node.getId() + ": " + nodeLayout + subgraphVisitor.layout + ")");
	}

	/////////////////////////////////////////////////////////////////////////
	struct EdgeLayout {
		EdgeLayout(const Edge& edge, GraphEasyLayoutContext& ctxt)
		: edge(edge), ctxt(ctxt) {
		}

		virtual ~EdgeLayout() {
		}

		std::string getLayout() const {
			auto graph = ctxt.getCurrentGraph();
			if (!graph) {
				EG_FATAL("Layout context has no graph!");
				return "";
			}

			auto [src, dst] = graph->findNodePair(edge);

			if ((!src) || (!dst)) {
				EG_FATAL("Layout context graph(%s) has not found nodes(%s, %s)!",
						graph->getName().c_str(),
						edge.getSrc().getNodeId().c_str(),
						edge.getDst().getNodeId().c_str());
				return "";
			}

			return getNodeBaseLayout(*src) + getArrowLayout() + getAttrLayout() + getNodeBaseLayout(*dst);
		}

	private:
		std::string getAttrLayout() const {
			auto edgeTypeLayout = trait_cast<GraphEasyEdgeLayoutTrait>(edge.getType());
			return edgeTypeLayout ? edgeTypeLayout->getAttrLayout(edge, ctxt) : "";
		}

		std::string getArrowLayout() const {
			auto edgeTypeLayout = trait_cast<GraphEasyEdgeLayoutTrait>(edge.getType());
			return edgeTypeLayout ? edgeTypeLayout->getArrowLayout(edge, ctxt) : " --> ";
		}

	protected:
		const Edge& edge;
		GraphEasyLayoutContext& ctxt;
	};
}

GraphEasyVisitor::GraphEasyVisitor(const GraphEasyOption& options)
: ctxt(options){
}

void GraphEasyVisitor::visit(const Graph& graph) {
	ctxt.enterGraph(graph);
	layout += getGraphLayoutTitle(graph, ctxt);
}

void GraphEasyVisitor::visit(const Node& node) {
	layout += getNodeLayout(node, ctxt);
}

void GraphEasyVisitor::visit(const Edge& edge) {
	EdgeLayout edgeLayout(edge, ctxt);
	layout += edgeLayout.getLayout();
}

std::string GraphEasyVisitor::getLayout() const {
	return layout;
}

EG_NS_END
