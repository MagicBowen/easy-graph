#ifndef H33A06A4E_58D3_454D_A62D_4D2A770D3FEF
#define H33A06A4E_58D3_454D_A62D_4D2A770D3FEF

#include "easy_graph/graph/graph_visitor.h"
#include "assertion/visitor/base_types.h"
#include <string>

EG_NS_BEGIN

struct Node;
struct Endpoint;

struct NodeAssertVisitor: GraphVisitor {
	NodeAssertVisitor(const Node&);

	size_t inputCount{0};
	size_t outputCount{0};

	bool isSource() const;
	bool isSink() const;
	bool isIsolated() const;

	bool prevNextTo(const NodeId&) const;
	bool postNextTo(const NodeId&) const;

	bool prevNextTo(const Endpoint&) const;
	bool postNextTo(const Endpoint&) const;

private:
	Status visit(const Edge&) override;

private:
	const Node& node;
	Edges prevEdges;
	Edges postEdges;
};

EG_NS_END

#endif
