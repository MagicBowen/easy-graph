#ifndef HFC457C7C_1FE9_4911_AA03_608480804680
#define HFC457C7C_1FE9_4911_AA03_608480804680

#include "easy_graph/graph/endpoint.h"
#include "easy_graph/graph/port_id.h"

EG_NS_BEGIN

struct Wire {
	Wire(const Endpoint&, const PortId&);

	__DECL_COMP(Wire);

	Endpoint getEndpoint() const;
	PortId   getPortId() const;

private:
	Endpoint endpoint;
	PortId   port;
};

struct InputWire : Wire {
	InputWire(const PortId& port, const Endpoint& endpoint)
	: Wire(endpoint, port) {
	}
};

struct OutputWire : Wire {
	OutputWire(const Endpoint& endpoint, const PortId& port)
	: Wire(endpoint, port) {
	}
};

EG_NS_END

#endif
