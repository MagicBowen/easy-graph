#ifndef HABAAF923_6E02_4802_8F8D_D556FE9B03E5
#define HABAAF923_6E02_4802_8F8D_D556FE9B03E5

#include "easy_graph/infra/singleton.h"
#include "easy_graph/graph/edge_type.h"
#include "easy_graph/builder/port_aware_trait.h"

EG_NS_BEGIN

SINGLETON(DataEdgeType) EXTENDS(EdgeType, PortAwareTrait) {
};

#define EDGE_DATA  ::EG_NS::DataEdgeType::getInstance()

EG_NS_END

#endif
