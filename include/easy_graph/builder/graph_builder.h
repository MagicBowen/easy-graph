#ifndef H5FED5F58_167D_4536_918A_D5FE8F28DD9C
#define H5FED5F58_167D_4536_918A_D5FE8F28DD9C

#include "easy_graph/graph/graph.h"

EG_NS_BEGIN

struct Link;

struct GraphBuilder {
	GraphBuilder(const std::string& name);

	Node*  buildNode(const Node&);
	void   buildEdge(const Node& src, const Node& dst, const Link&);

	Graph& operator*()
    {
        return graph;
    }

    const Graph& operator*() const
    {
        return graph;
    }

    Graph* operator->()
    {
        return &graph;
    }

    const Graph* operator->() const
    {
        return &graph;
    }

private:
	struct NodeInfo {
		PortId inPortMax{0};
		PortId outPortMax{0};
	};

	NodeInfo* findNode(const NodeId&);
	const NodeInfo* findNode(const NodeId&) const;

private:
	std::map<NodeId, NodeInfo> nodes;
	Graph graph;
};

EG_NS_END

#endif
