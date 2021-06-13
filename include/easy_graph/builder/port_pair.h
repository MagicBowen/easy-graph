#ifndef HBE043731_326D_4E49_9BE2_177C66F8710D
#define HBE043731_326D_4E49_9BE2_177C66F8710D

#include "easy_graph/graph/port_id.h"
#include <utility>

EG_NS_BEGIN

using PortPair = std::pair<PortId, PortId>;

#define PP(SRC, DST)  std::make_pair(PortId(SRC), PortId(DST))

EG_NS_END

#endif
