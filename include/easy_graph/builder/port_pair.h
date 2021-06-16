#ifndef HBE043731_326D_4E49_9BE2_177C66F8710D
#define HBE043731_326D_4E49_9BE2_177C66F8710D

#include "easy_graph/graph/port_id.h"
#include <utility>

EG_NS_BEGIN

using PortPair = std::pair<PortId, PortId>;

static inline PortPair pp_of(PortId src, PortId dst) {
	return std::make_pair(src, dst);
}

EG_NS_END

#endif
