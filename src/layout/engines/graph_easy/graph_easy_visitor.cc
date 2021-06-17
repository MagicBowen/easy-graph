#include "easy_graph/layout/engines/graph_easy/graph_easy_visitor.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_edge_layout_trait.h"
#include "easy_graph/builder/port_aware_trait.h"
#include "easy_graph/graph/subgraph_visitor.h"
#include "easy_graph/graph/wire_visitor.h"
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
	std::string to_layout(const std::string& str) {
		return str;
	}

	std::string to_layout(const PortId& id) {
		return std::to_string(id);
	}

	std::string to_layout(const Endpoint& ep) {
		return ep.getNodeId() + "." + to_layout(ep.getPortId());
	}

	std::string to_layout(const InputWire& iw) {
		return std::string("(") + to_layout(iw.getPortId()) + ", " + to_layout(iw.getEndpoint()) + ")";
	}

	std::string to_layout(const OutputWire& ow) {
		return std::string("(") + to_layout(ow.getEndpoint()) + ", " + to_layout(ow.getPortId()) + ")";
	}

	std::string to_layout(const Node& node) {
		return std::string("[") + node.getId() + "]";
	}

	std::string to_layout(const NodeId& id, const Subgraph& subgraph, bool isBref = true) {
		auto result = std::string("[") + id + "/" + subgraph.getName() + "]";
		auto display = "{class : subgraph; label : " + subgraph.getName() + ";}";
		return isBref ? result : result + display;
	}

	template<typename T>
	std::string to_label_layout(const T& t){
		return std::string("{ label : ") + to_layout(t)  + " }";
	}

	/////////////////////////////////////////////////////////////////////////
	struct SubgraphWireLayoutVisitor : WireVisitor {
		SubgraphWireLayoutVisitor(const std::string& node, const std::string& subgraph, GraphEasyLayoutContext& ctxt)
		: nodeLayout(node), subgraphLayout(subgraph), ctxt(ctxt) {
		}
		std::string layout;
		bool hasWired{false};

	private:
		void visit(const InputWire& wire) override {
			layout += (nodeLayout + arrow + to_label_layout(wire) + subgraphLayout);
			hasWired = true;
		}

		void visit(const OutputWire& wire) override {
			layout += (subgraphLayout + arrow + to_label_layout(wire) + nodeLayout);
			hasWired = true;
		}

	private:
		const std::string nodeLayout;
		const std::string subgraphLayout;
		GraphEasyLayoutContext& ctxt;
		static constexpr const char* arrow = " ..-> ";
	};

	/////////////////////////////////////////////////////////////////////////
	struct SubgraphLayoutVisitor : SubgraphVisitor {
		SubgraphLayoutVisitor(const Node& node, GraphEasyLayoutContext& ctxt)
		: node(node), ctxt(ctxt) {
		}
		std::string layout;
		bool hasSubgraph{false};

	private:
		void visit(const Subgraph& subgraph) override {
			AUTO_GUARD([this, &subgraph](){ctxt.enterGraph(subgraph.getGraph());}, [this](){ctxt.exitGraph();});

			layout += to_layout(node.getId(), subgraph, false);

			SubgraphWireLayoutVisitor wireVisitor(to_layout(node), to_layout(node.getId(), subgraph), ctxt);
			subgraph.accept(wireVisitor);

			if (wireVisitor.hasWired) {
				layout += wireVisitor.layout;
			} else {
				layout += (to_layout(node) + arrow + to_layout(node.getId(), subgraph));
			}

			hasSubgraph = true;
		}

	private:
		const Node& node;
		GraphEasyLayoutContext& ctxt;
		static constexpr const char* arrow = " .. ";
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
		auto id = node.getId();
		std::string nodeLayout = to_layout(node);

		SubgraphLayoutVisitor visitor(node, ctxt);
		node.accept(visitor);
		if (!visitor.hasSubgraph) return nodeLayout;

		return (std::string("( ") + node.getId() + ": " + nodeLayout + visitor.layout + ")");
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

			return to_layout(*src) + getArrowLayout() + getAttrLayout() + to_layout(*dst);
		}

	private:
		std::string getAttrLayout() const {
			auto label = getLabel();

			if (isPortAware()) {
				return std::string("{ ") + std::string("label :") + label + getPortPair() + "; " + getPortAttr() + " }";
			}

			if (label == "") return "";
			return to_label_layout(label);
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
