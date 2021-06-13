#ifndef H1862D663_769E_4D7D_B59A_23D7350EB7C0
#define H1862D663_769E_4D7D_B59A_23D7350EB7C0

#include "easy_graph/infra/singleton.h"
#include "easy_graph/graph/edge_type.h"
#include "easy_graph/builder/port_aware_trait.h"

EG_NS_BEGIN

SINGLETON(DefaultEdgeType) EXTENDS(EdgeType, PortAwareTrait) {
};

#define DEFAULT_EDGE  ::EG_NS::DefaultEdgeType::getInstance()

EG_NS_END

#endif
