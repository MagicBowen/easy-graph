#ifndef H04F4EEC1_7AEB_4D92_87F5_556925941F4E
#define H04F4EEC1_7AEB_4D92_87F5_556925941F4E

#include "easy_graph/graph/endpoint.h"

EG_NS_BEGIN

static inline Endpoint ep_of(const NodeId& node, PortId port = 0) {
	return Endpoint(node, port);
}

EG_NS_END

#endif
