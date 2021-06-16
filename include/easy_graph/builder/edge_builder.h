#ifndef H26FB68B9_7EA7_4091_B4BB_32DD6BD1B99F
#define H26FB68B9_7EA7_4091_B4BB_32DD6BD1B99F

#include "easy_graph/edges/default_edge_type.h"
#include "easy_graph/edges/data_edge_type.h"
#include "easy_graph/edges/ctrl_edge_type.h"

EG_NS_BEGIN

static inline const EdgeType& default_edge() {
	return DefaultEdgeType::getInstance().get();
}

static inline const EdgeType& data_edge() {
	return DataEdgeType::getInstance();
}

static inline const EdgeType& ctrl_edge() {
	return CtrlEdgeType::getInstance();
}

EG_NS_END

#endif
