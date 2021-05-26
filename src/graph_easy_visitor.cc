#include "graph_easy_visitor.h"
#include "shell_executor.h"
#include "graph_easy_option.h"
#include "auto_switch.h"
#include "graph.h"
#include "edge.h"
#include "node.h"

EG_NS_BEGIN

namespace {
	struct SubgraphLayoutVisitor : GraphVisitor {
		SubgraphLayoutVisitor(const NodeId& id, GraphEasyLayoutContext& ctxt)
		: id(id), ctxt(ctxt) {
		}
		std::string layout;

	private:
		Status visit(const Graph& graph) override {
			layout += (std::string(" -- [") + id + "/" + graph.getName() + "]" + "{class : subgraph; label : " + graph.getName() + ";}");
			return EG_SUCCESS;
		}
	private:
		NodeId id;
		GraphEasyLayoutContext& ctxt;
	};

	std::string getNodeLayout(const Node& node, GraphEasyLayoutContext& ctxt) {
		const auto& id = node.getId();
		std::string nodeBox = std::string("[") + id + "]";

		if (!node.hasSubgraph() || ctxt.inLinking()) return nodeBox;

		SubgraphLayoutVisitor subgraphVisitor(id, ctxt);
		node.accept(subgraphVisitor);

		return (std::string("( ") + id + ": " + nodeBox + subgraphVisitor.layout + ")");
	}

	INTERFACE(EdgeLayout) {
		EdgeLayout(GraphEasyLayoutContext& ctxt,
				   const Edge& edge)
		: ctxt(ctxt), options(ctxt.getOptions()), edge(edge){
		}

		std::string getLayout() const {
			std::string srcNodeLayout = getNodeLayout(edge.getSrc().getNode(), ctxt);
			std::string dstNodeLayout = getNodeLayout(edge.getDst().getNode(), ctxt);
			return srcNodeLayout + getArrowLayout() + getAttrLayout() + dstNodeLayout;
		}

	private:
		ABSTRACT(std::string getAttrLayout() const);
		ABSTRACT(std::string getArrowLayout() const);

	protected:
		GraphEasyLayoutContext& ctxt;
		const GraphEasyOption& options;
		const Edge& edge;
	};

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

Status GraphEasyVisitor::visit(const Graph& graph) {
	std::string flowDirection = (ctxt.getOptions().dir == FlowDir::LR) ? "east" : "down";
	std::string graphTitle = std::string("graph { label : ")
			               + graph.getName()
						   +  "; flow : "
						   + flowDirection + " ; } node.subgraph { border : double-dash; }";
	layout += graphTitle;
	return EG_SUCCESS;
}

Status GraphEasyVisitor::visit(const Node& node) {
	layout += getNodeLayout(node, ctxt);
	return EG_SUCCESS;
}

Status GraphEasyVisitor::visit(const Edge& edge) {
	AutoSwitch autoSwitch([this](){ctxt.linkBegin();}, [this](){ctxt.linkEnd();});

	auto makeEdgeLayout = [this, &edge]() -> const EdgeLayout*{
		if (edge.getType() == EdgeType::CTRL_EDGE) return new CtrlEdgeLayout(ctxt, edge);
		return new DataEdgeLayout(ctxt, edge);
	};

	std::unique_ptr<const EdgeLayout> edgeLayout(makeEdgeLayout());
	layout += edgeLayout->getLayout();
	return EG_SUCCESS;
}

std::string GraphEasyVisitor::getLayout() const {
	return layout;
}

EG_NS_END
