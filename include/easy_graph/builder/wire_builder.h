#ifndef H54099A0C_BC2E_43D4_ABE2_9875362AEFE1
#define H54099A0C_BC2E_43D4_ABE2_9875362AEFE1

#include "easy_graph/graph/endpoint.h"
#include "easy_graph/graph/wire.h"

EG_NS_BEGIN

static inline Endpoint ep_of(const NodeId& node, const PortId& port) {
	return Endpoint(node, port);
}

static inline InputWire iw_of(const PortId& port, const Endpoint& ep) {
	return InputWire(port, ep);
}

static inline OutputWire ow_of(const Endpoint& ep, const PortId& port) {
	return OutputWire(ep, port);
}

EG_NS_END

#endif
