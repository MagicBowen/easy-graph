#include "easy_graph/graph/edge_type.h"

#include "easy_graph/layout/engines/graph_easy/graph_easy_edge_layout_trait.h"
#include "easy_graph/builder/port_aware_trait.h"

EG_NS_BEGIN

namespace {
	struct CtrlEdgeType : EdgeType, GraphEasyEdgeLayoutTrait {
	private:
		std::string getArrow() const override {
			return " ..> ";
		}
	};

	struct DataEdgeType : EdgeType, PortAwareTrait {
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
