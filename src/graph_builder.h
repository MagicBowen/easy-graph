#ifndef H5FED5F58_167D_4536_918A_D5FE8F28DD9C
#define H5FED5F58_167D_4536_918A_D5FE8F28DD9C

#include "graph.h"

EG_NS_BEGIN

struct GraphBuilder {
	GraphBuilder(const std::string& name);

	Node* addNode(const Node&);
	void addEdge(EdgeType, const std::string& label, Node& src, Node& dst);

	Graph& getGraph();
	const Graph& getGraph() const;

private:
	struct NodeInfo {
		size_t jointInNum{0};
		size_t jointOutNum{0};
	};

	NodeInfo* findNode(const NodeId&);
	const NodeInfo* findNode(const NodeId&) const;

private:
	std::map<NodeId, NodeInfo> nodes;
	Graph graph;
};

EG_NS_END

#endif
