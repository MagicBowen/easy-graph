#ifndef HF37ACE88_F726_4AA3_8599_ED7A888AA623
#define HF37ACE88_F726_4AA3_8599_ED7A888AA623

#include "easy_graph/graph/node_id.h"
#include "easy_graph/infra/cmp_helper.h"
#include <vector>

EG_NS_BEGIN

struct Graph;
struct GraphVisitor;

struct Node
{
    explicit Node(const NodeId& id);
    Node(const char* id);

    template<typename ...GRAPHS>
    Node(const NodeId& id, const GRAPHS&... graphs)
	: id(id), subgraphs{&graphs...}{
    }

    __DECL_COMP(Node);

    NodeId getId() const;

    bool hasSubgraph() const;
    void accept(GraphVisitor&) const;

private:
    NodeId id;
    std::vector<const Graph*> subgraphs;
};

EG_NS_END

#endif
