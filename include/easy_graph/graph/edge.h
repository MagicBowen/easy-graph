#ifndef HE62943BF_1F7C_4EF9_B306_D9C94634EA74
#define HE62943BF_1F7C_4EF9_B306_D9C94634EA74

#include "easy_graph/graph/edge_type.h"
#include "easy_graph/graph/node_port.h"
#include "easy_graph/graph/endpoint.h"
#include <string>

EG_NS_BEGIN

struct Edge
{
	Edge(const EdgeType type,
		 const std::string& label,
		 const NodePort& src,
		 const NodePort& dst);

	__DECL_COMP(Edge);

	EdgeType getType() const;
	std::string getLabel() const;

	const Node& getSrcNode() const;
	const Node& getDstNode() const;

	Endpoint getSrcEndpoint() const;
	Endpoint getDstEndpoint() const;

private:
	std::string label;
	EdgeType type;
	NodePort src;
	NodePort dst;
};

EG_NS_END

#endif
