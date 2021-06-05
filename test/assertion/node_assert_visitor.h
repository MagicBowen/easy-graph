#ifndef H33A06A4E_58D3_454D_A62D_4D2A770D3FEF
#define H33A06A4E_58D3_454D_A62D_4D2A770D3FEF

#include "easy_graph/graph/graph_visitor.h"
#include "assertion/base_types.h"
#include <string>

EG_NS_BEGIN

struct Node;

struct NodeAssertVisitor: GraphVisitor {
	NodeAssertVisitor(const Node& node);

	size_t prevEdgeCount{0};
	size_t postEdgeCount{0};

	bool prevNextTo(const NodeId& id) const;
	bool postNextTo(const NodeId& id) const;

private:
	Status visit(const Graph& graph) override;
	Status visit(const Node& node) override;
	Status visit(const Edge& edge) override;

private:
	const Node& node;
	Edges prevEdges;
	Edges postEdges;
};

EG_NS_END

#endif
