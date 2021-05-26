#include "edge.h"
#include "node.h"
#include "layout_option.h"
#include "layout_context.h"

EG_NS_BEGIN

Edge::Edge(const EdgeType type,
		   const std::string& label,
		   const NodePort& src,
		   const NodePort& dst)
: type(type), label(label), src(src),dst(dst) {
}

__DEF_EQUALS(Edge)
{
	return  (type == rhs.type) && (src == rhs.src) && (dst == rhs.dst);
}

__DEF_COMP(Edge)
{
	if (src < rhs.src) return true;
	if ((src == rhs.src) && (dst < rhs.dst)) return true;
	if ((src == rhs.src) && (dst < rhs.dst) && (type < rhs.type)) return true;
	return false;
}

namespace {
	INTERFACE(EdgeLayout) {
		EdgeLayout(LayoutContext& context,
				   const std::string& label,
				   const NodePort& src,
				   const NodePort& dst)
		: context(context), options(context.getOptions()), label(label), src(src), dst(dst){
		}

		std::string getLayout() const {
			const Layoutable& srcLayoutable = src.getNode();
			const Layoutable& dstLayoutable = dst.getNode();
			return srcLayoutable.getLayout(context) + getArrowLayout() + getAttrLayout() + dstLayoutable.getLayout(context);
		}

	private:
		ABSTRACT(std::string getAttrLayout() const);
		ABSTRACT(std::string getArrowLayout() const);

	protected:
		LayoutContext& context;
		const LayoutOption& options;
		const std::string& label;
		const NodePort& src;
		const NodePort& dst;
	};

	struct CtrlEdgeLayout : EdgeLayout {
		using EdgeLayout::EdgeLayout;
	private:
		std::string getAttrLayout() const override {
			if (label == "") return "";
			return std::string("{label : ") + label  + "}";
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
			return std::string("(")+ std::to_string(src.getPortId()) + "," + std::to_string(dst.getPortId()) + ")";
		}

		std::string getLabelAttr() const {
			return std::string("label :") + label + getPortPair() + "; ";
		}

		std::string getPortAttr() const {
			return (options.type == LayoutType::FREE) ? "" : getOutPortAttr() + getInPortAttr();
		}

		std::string getOutPortAttr() const {
			return std::string(" start : ") + "front" + ", " + std::to_string(src.getPortId() * options.scale) + "; ";
		}

		std::string getInPortAttr() const {
			return std::string(" end : ") + "back" + ", " + std::to_string(dst.getPortId() * options.scale) + "; ";
		}
	};
}

std::string Edge::getLayout(LayoutContext& context) const {

	auto makeEdgeLayout = [this, &context]() -> const EdgeLayout*{
		if (type == CTRL_EDGE) return new CtrlEdgeLayout(context, label, src, dst);
		return new DataEdgeLayout(context, label, src, dst);
	};

	std::unique_ptr<const EdgeLayout> layout(makeEdgeLayout());
	return layout->getLayout();
}

EG_NS_END
