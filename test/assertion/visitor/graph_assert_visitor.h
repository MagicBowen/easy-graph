#ifndef HEBB3A35C_0E93_4823_94CE_64E7F2006AF2
#define HEBB3A35C_0E93_4823_94CE_64E7F2006AF2

#include "easy_graph/graph/graph_visitor.h"
#include "assertion/visitor/base_types.h"
#include "easy_graph/graph/edge_type.h"
#include <map>

EG_NS_BEGIN

struct Endpoint;

struct GraphAssertVisitor: GraphVisitor {
	std::string name;
	size_t nodeCount{0};
	size_t edgeCount{0};

    bool isEqualTo(const Graph&) const;

	bool hasNode(const NodeId&) const;

	bool hasEdge(const NodeId& src,
			     const NodeId& dst,
				 EdgeType type = EdgeType::DATA) const;

	bool hasEdge(const Endpoint& src,
			     const Endpoint& dst,
				 EdgeType type = EdgeType::DATA) const;

private:
	void visit(const Graph&) override;
	void visit(const Node&) override;
	void visit(const Edge&) override;

private:
	template<typename PRED>
	bool isEdgeExisted(EdgeType type, PRED pred) const;

private:
	const Graph* graph{nullptr};
	Edges edges;
};

EG_NS_END

#endif
