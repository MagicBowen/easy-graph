#include "easy_graph/graph/edge_type.h"

#include "easy_graph/layout/engines/graph_easy/graph_easy_edge_layout_trait.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_layout_context.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "easy_graph/builder/auto_link_port_trait.h"
#include "easy_graph/graph/edge.h"

EG_NS_BEGIN

namespace {

/////////////////////////////////////////////////////////////////////////
struct CtrlEdgeLayout : GraphEasyEdgeLayoutTrait {
private:
	std::string getAttrLayout(const Edge& edge, GraphEasyLayoutContext&) const override {
		auto label = edge.getAttr<const char*>("label");
		if (!label || std::string(*label) == "") return "";
		return std::string("{label : ") + *label  + "}";
	}

	std::string getArrowLayout(const Edge&, GraphEasyLayoutContext&) const override {
		return " ..> ";
	}
};

/////////////////////////////////////////////////////////////////////////
struct DataEdgeLayout : GraphEasyEdgeLayoutTrait  {
private:
	std::string getAttrLayout(const Edge& edge, GraphEasyLayoutContext& ctxt) const override {
		return std::string("{ ") + getLabelAttr(edge) + getPortAttr(edge, ctxt.getOptions()) + " }";
	}

	std::string getArrowLayout(const Edge&, GraphEasyLayoutContext&) const override {
		return " --> ";
	}

private:
	std::string getPortPair(const Edge& edge) const {
		return std::string("(")+ std::to_string(edge.getSrc().getPortId()) + "," + std::to_string(edge.getDst().getPortId()) + ")";
	}

	std::string getLabelAttr(const Edge& edge) const {
		std::string label;
		auto labelAttr = edge.getAttr<const char*>("label");
		if (labelAttr) label = *labelAttr;
		return std::string("label :") + label + getPortPair(edge) + "; ";
	}

	std::string getPortAttr(const Edge& edge, const GraphEasyOption& option) const {
		return (option.type == LayoutType::FREE) ? "" : getOutPortAttr(edge, option) + getInPortAttr(edge, option);
	}

	std::string getOutPortAttr(const Edge& edge, const GraphEasyOption& option) const {
		return std::string(" start : ") + "front" + ", " + std::to_string(edge.getSrc().getPortId() * option.scale) + "; ";
	}

	std::string getInPortAttr(const Edge& edge, const GraphEasyOption& option) const {
		return std::string(" end : ") + "back" + ", " + std::to_string(edge.getDst().getPortId() * option.scale) + "; ";
	}
};



	struct CtrlEdgeType : EdgeType, CtrlEdgeLayout {
	};

	struct DataEdgeType : EdgeType, DataEdgeLayout, AutoLinkPortTrait {
	};
}

EdgeType& EdgeType::CTRL() {
	static CtrlEdgeType edge;
	return edge;
}

EdgeType& EdgeType::DATA() {
	static DataEdgeType edge;
	return edge;
}

__DEF_EQUALS(EdgeType)
{
	return  (typeid(*this) == typeid(rhs));
}

__DEF_COMP(EdgeType)
{
	return (typeid(*this).name() < typeid(rhs).name());
}

EG_NS_END
