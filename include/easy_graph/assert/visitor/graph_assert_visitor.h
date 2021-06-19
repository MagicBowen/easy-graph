#ifndef HEBB3A35C_0E93_4823_94CE_64E7F2006AF2
#define HEBB3A35C_0E93_4823_94CE_64E7F2006AF2

#include "easy_graph/graph/graph_visitor.h"
#include "easy_graph/graph/node_id.h"
#include <string>

EG_NS_BEGIN

struct GraphAssertVisitor: GraphVisitor {
	std::string name;
	size_t nodeCount{0};
	size_t edgeCount{0};

    bool isEqualTo(const Graph&) const;
	bool hasNode(const NodeId&) const;
	bool hasEdge(const Edge&) const;
	void dump() const;

private:
	void visit(const Graph&) override;
	void visit(const Node&) override;
	void visit(const Edge&) override;

private:
	const Graph* graph{nullptr};
};

EG_NS_END

#endif
