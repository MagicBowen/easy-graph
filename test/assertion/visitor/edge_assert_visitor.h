#ifndef H835D1C92_F2A5_482D_A021_711F0ACC271B
#define H835D1C92_F2A5_482D_A021_711F0ACC271B

#include "assertion/visitor/base_types.h"
#include "easy_graph/graph/graph_visitor.h"
#include "easy_graph/graph/port_id.h"

EG_NS_BEGIN

struct EdgeAssertVisitor: GraphVisitor {
	EdgeAssertVisitor(const Node& src, const Node& dst);

	size_t count{0};
	bool linked(const PortId& src, const PortId& dst) const;

	bool isCtrlType() const;
	bool isDataType(const PortId& src, const PortId& dst) const;

private:
	Status visit(const Edge&) override;

private:
	const Edge* findEdge(const PortId& src, const PortId& dst) const;

private:
	const Node& srcNode;
	const Node& dstNode;
	Edges edges;
};

EG_NS_END

#endif