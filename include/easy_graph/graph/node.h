#ifndef HF37ACE88_F726_4AA3_8599_ED7A888AA623
#define HF37ACE88_F726_4AA3_8599_ED7A888AA623

#include "easy_graph/graph/node_id.h"
#include "easy_graph/infra/operator.h"
#include <vector>

EG_NS_BEGIN

struct Graph;
struct GraphVisitor;
struct Box;

struct Node
{
    explicit Node(const NodeId& id);
    Node(const char* id);

    Node(const Box& box);

    template<typename ...GRAPHS>
    Node(const NodeId& id, const GRAPHS&... graphs)
	: id(id), subgraphs{&graphs...}{
    }

    __DECL_COMP(Node);

    NodeId getId() const;

    const Box* getBox() const;

    bool hasSubgraph() const;
    void accept(GraphVisitor&) const;

private:
    NodeId id;
    const Box* box{nullptr};
    std::vector<const Graph*> subgraphs;
};

EG_NS_END

#endif
