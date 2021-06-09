#ifndef HF37ACE88_F726_4AA3_8599_ED7A888AA623
#define HF37ACE88_F726_4AA3_8599_ED7A888AA623

#include "easy_graph/graph/node_id.h"
#include "easy_graph/infra/operator.h"
#include "easy_graph/infra/ext_traits.h"
#include "easy_graph/graph/subgraph.h"
#include "easy_graph/graph/box.h"
#include <vector>

EG_NS_BEGIN

struct SubgraphVisitor;

struct Node
{
    template<typename ...SUBGRAPHS, SUBGRAPH_CONCEPT(SUBGRAPHS, Subgraph)>
    Node(const NodeId& id, const SUBGRAPHS&... subgraphs)
	: id(id), subgraphs{subgraphs...} {
    }
    
    template<typename ...SUBGRAPHS, SUBGRAPH_CONCEPT(SUBGRAPHS, Subgraph)>
    Node(const NodeId& id, const BoxPtr& box, const SUBGRAPHS&... subgraphs)
	: id(id), box(box), subgraphs{subgraphs...} {
    }

    __DECL_COMP(Node);

    NodeId getId() const;

    Node& packing(const BoxPtr&);

    template<typename Anything>
    Anything* unpacking() const {
    	if(!box) return nullptr;
    	return box_unpacking<Anything>(box);
    }

    Node& addSubgraph(const Subgraph&);

    void accept(SubgraphVisitor&) const;

private:
    NodeId id;
    BoxPtr box;
    std::vector<Subgraph> subgraphs;
};

EG_NS_END

#endif
