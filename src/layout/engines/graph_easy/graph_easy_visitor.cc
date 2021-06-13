#include "easy_graph/layout/engines/graph_easy/graph_easy_visitor.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_edge_layout_trait.h"
#include "easy_graph/builder/port_aware_trait.h"
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
		: edge(edge), ctxt(ctxt), option(ctxt.getOptions()) {
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
			auto label = getLabel();

			if (isPortAware()) {
				return std::string("{ ") + std::string("label :") + label + getPortPair() + "; " + getPortAttr() + " }";
			}

			if (label == "") return "";
			return std::string("{ label : ") + label  + " }";
		}

		std::string getArrowLayout() const {
			auto edgeTypeLayout = trait_cast<GraphEasyEdgeLayoutTrait>(edge.getType());
			return edgeTypeLayout ? edgeTypeLayout->getArrow() : " --> ";
		}

		std::string getLabel() const {
			auto labelAttr = edge.getAttr<const char*>("label");
			if (!labelAttr) return "";
			return *labelAttr;
		}

		bool isPortAware() const {
			return (trait_cast<PortAwareTrait>(edge.getType()) != nullptr);
		}

		std::string getPortPair() const {
			return std::string("(")+ std::to_string(edge.getSrc().getPortId()) + "," + std::to_string(edge.getDst().getPortId()) + ")";
		}

		std::string getPortAttr() const {
			return (option.type == LayoutType::FREE) ? "" : getOutPortAttr() + getInPortAttr();
		}

		std::string getOutPortAttr() const {
			return std::string(" start : ") + "front" + ", " + std::to_string(edge.getSrc().getPortId() * option.scale) + "; ";
		}

		std::string getInPortAttr() const {
			return std::string(" end : ") + "back" + ", " + std::to_string(edge.getDst().getPortId() * option.scale) + "; ";
		}

	protected:
		const Edge& edge;
		GraphEasyLayoutContext& ctxt;
		const GraphEasyOption& option;
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
