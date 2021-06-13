#include "easy_graph/graph/edge_type.h"
#include <string>

EG_NS_BEGIN

__DEF_EQUALS(EdgeType)
{
	return  (typeid(*this) == typeid(rhs));
}

__DEF_COMP(EdgeType)
{
	return (typeid(*this).name() < typeid(rhs).name());
}

EG_NS_END
