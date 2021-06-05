#ifndef HEBB3A35C_0E93_4823_94CE_64E7F2006AF2
#define HEBB3A35C_0E93_4823_94CE_64E7F2006AF2

#include "easy_graph/graph/graph_visitor.h"
#include "assertion/base_types.h"
#include <string>
#include <map>

EG_NS_BEGIN

struct GraphAssertVisitor: GraphVisitor {
	std::string name;
	size_t nodeCount{0};
	size_t edgeCount{0};

    bool isEqualTo(const Graph&) const;
	bool hasNode(const NodeId& id) const;
	bool hasEdge(const NodeId& src, const NodeId& dst) const;

private:
	Status visit(const Graph& graph) override;
	Status visit(const Node& node) override;
	Status visit(const Edge& edge) override;

private:
	const Graph* graph{nullptr};
	std::map<NodeId, Edges> nodeEdges;
};

EG_NS_END

#endif
