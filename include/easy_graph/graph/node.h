#ifndef HF37ACE88_F726_4AA3_8599_ED7A888AA623
#define HF37ACE88_F726_4AA3_8599_ED7A888AA623

#include "easy_graph/graph/node_id.h"
#include "easy_graph/infra/operator.h"
#include "easy_graph/infra/ext_traits.h"
#include "easy_graph/graph/box.h"
#include <vector>

EG_NS_BEGIN

struct GraphVisitor;
struct Graph;

struct Node
{
    template<typename ...GRAPHS, SUBGRAPH_CONCEPT(GRAPHS, Graph)>
    Node(const NodeId& id, const GRAPHS&... graphs)
	: id(id), subgraphs{&graphs...} {
    }
    
    template<typename ...GRAPHS, SUBGRAPH_CONCEPT(GRAPHS, Graph)>
    Node(const NodeId& id, const BoxPtr& box, const GRAPHS&... graphs)
	: id(id), box(box), subgraphs{&graphs...} {
    }

    __DECL_COMP(Node);

    NodeId getId() const;

    void packing(const BoxPtr& box);

    template<typename Anything>
    Anything* unpacking() const {
    	if(!box) return nullptr;
    	return box_unpacking<Anything>(box);
    }

    void addSubgraph(const Graph&);
    void accept(GraphVisitor&) const;

private:
    NodeId id;
    BoxPtr box;
    std::vector<const Graph*> subgraphs;
};

EG_NS_END

#endif
