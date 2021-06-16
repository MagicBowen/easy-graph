#include "easy_graph/edges/default_edge_type.h"
#include "easy_graph/builder/port_aware_trait.h"
#include "easy_graph/graph/edge_type.h"

EG_NS_BEGIN

namespace {
 	 struct DefaultEdgeTypeImpl : EdgeType, PortAwareTrait {
 	 } defaultType;
}

void DefaultEdgeType::reg(const EdgeType& type) {
	this->type = &type;
}

const EdgeType& DefaultEdgeType::get() const {
	return type ? *type : defaultType;
}

void DefaultEdgeType::reset() {
	type = nullptr;
}

EG_NS_END
