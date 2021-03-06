#ifndef HE62943BF_1F7C_4EF9_B306_D9C94634EA74
#define HE62943BF_1F7C_4EF9_B306_D9C94634EA74

#include "easy_graph/graph/endpoint.h"
#include "easy_graph/attribute/attributes_mixin.h"

EG_NS_BEGIN

struct EdgeType;

struct Edge : AttributesMixin
{
	Edge(const EdgeType& type,
		 const Endpoint& src,
		 const Endpoint& dst);

	__DECL_COMP(Edge);

	const EdgeType& getType() const;

	Endpoint getSrc() const;
	Endpoint getDst() const;

private:
	const EdgeType& type;
	Endpoint src;
	Endpoint dst;
};

EG_NS_END

#endif
