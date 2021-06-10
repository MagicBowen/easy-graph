#include "easy_graph/layout/engines/graph_easy/graph_easy_visitor.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "layout/engines/graph_easy/utils/shell_executor.h"
#include "easy_graph/graph/subgraph_visitor.h"
#include "easy_graph/infra/scope_guard.h"
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
		bool hasSubgraph{false};

	private:
		void visit(const Subgraph& subgraph) override {
			ScopeGuard guard([this, &subgraph](){ctxt.enterGraph(subgraph.getGraph());}, [this](){ctxt.exitGraph();});
			layout += (std::string(" -- [") + id + "/" + subgraph.getName() + "]" + "{class : subgraph; label : " + subgraph.getName() + ";}");
			hasSubgraph = true;
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
	std::string getNodeLayout(const Node& node, GraphEasyLayoutContext& ctxt) {
		const auto& id = node.getId();
		std::string nodeBox = std::string("[") + id + "]";

		SubgraphLayoutVisitor subgraphVisitor(id, ctxt);
		node.accept(subgraphVisitor);

		if (!subgraphVisitor.hasSubgraph || ctxt.inLinking()) return nodeBox;

		return (std::string("( ") + id + ": " + nodeBox + subgraphVisitor.layout + ")");
	}

	/////////////////////////////////////////////////////////////////////////
	INTERFACE(EdgeLayout) {
		EdgeLayout(GraphEasyLayoutContext& ctxt,
				   const Edge& edge)
		: ctxt(ctxt), options(ctxt.getOptions()), edge(edge){
		}

		std::string getLayout() const {
			auto graph = ctxt.getCurrentGraph();
			if (!graph) {
				EG_FATAL("Layout context has no graph!");
				return "";
			}

			auto [src, dst] = graph->findNodePair(edge);

			if ((!src) || (!dst)) {
				EG_FATAL("Layout context graph(%s) has not found node(%s, %s)!",
						graph->getName().c_str(),
						edge.getSrc().getNodeId().c_str(),
						edge.getDst().getNodeId().c_str());
				return "";
			}

			return getNodeLayout(*src, ctxt) + getArrowLayout() + getAttrLayout() + getNodeLayout(*dst, ctxt);
		}

	private:
		ABSTRACT(std::string getAttrLayout() const);
		ABSTRACT(std::string getArrowLayout() const);

	protected:
		GraphEasyLayoutContext& ctxt;
		const GraphEasyOption& options;
		const Edge& edge;
	};

	/////////////////////////////////////////////////////////////////////////
	struct CtrlEdgeLayout : EdgeLayout {
		using EdgeLayout::EdgeLayout;
	private:
		std::string getAttrLayout() const override {
			if (edge.getLabel() == "") return "";
			return std::string("{label : ") + edge.getLabel()  + "}";
		}

		std::string getArrowLayout() const override {
			return " ..> ";
		}
	};

	/////////////////////////////////////////////////////////////////////////
	struct DataEdgeLayout : EdgeLayout {
		using EdgeLayout::EdgeLayout;
	private:
		std::string getAttrLayout() const override {
			return std::string("{ ") + getLabelAttr() + getPortAttr() + " }";
		}

		std::string getArrowLayout() const override {
			return " --> ";
		}

	private:
		std::string getPortPair() const {
			return std::string("(")+ std::to_string(edge.getSrc().getPortId()) + "," + std::to_string(edge.getDst().getPortId()) + ")";
		}

		std::string getLabelAttr() const {
			return std::string("label :") + edge.getLabel() + getPortPair() + "; ";
		}

		std::string getPortAttr() const {
			return (options.type == LayoutType::FREE) ? "" : getOutPortAttr() + getInPortAttr();
		}

		std::string getOutPortAttr() const {
			return std::string(" start : ") + "front" + ", " + std::to_string(edge.getSrc().getPortId() * options.scale) + "; ";
		}

		std::string getInPortAttr() const {
			return std::string(" end : ") + "back" + ", " + std::to_string(edge.getDst().getPortId() * options.scale) + "; ";
		}
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
	ScopeGuard guard([this](){ctxt.linkBegin();}, [this](){ctxt.linkEnd();});

	auto makeEdgeLayout = [this, &edge]() -> const EdgeLayout* {
		if (edge.getType() == EdgeType::CTRL) return new CtrlEdgeLayout(ctxt, edge);
		return new DataEdgeLayout(ctxt, edge);
	};

	std::unique_ptr<const EdgeLayout> edgeLayout(makeEdgeLayout());
	layout += edgeLayout->getLayout();
}

std::string GraphEasyVisitor::getLayout() const {
	return layout;
}

EG_NS_END
