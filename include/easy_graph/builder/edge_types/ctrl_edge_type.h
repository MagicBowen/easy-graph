#ifndef H82A21037_C903_48E9_A02B_3E49A4504FFC
#define H82A21037_C903_48E9_A02B_3E49A4504FFC

#include "easy_graph/infra/singleton.h"
#include "easy_graph/graph/edge_type.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_edge_layout_trait.h"

EG_NS_BEGIN

SINGLETON(CtrlEdgeType) EXTENDS(EdgeType, GraphEasyEdgeLayoutTrait) {
private:
	std::string getArrow() const override {
		return " ..> ";
	}
};

#define EDGE_CTRL  ::EG_NS::CtrlEdgeType::getInstance()

EG_NS_END

#endif
