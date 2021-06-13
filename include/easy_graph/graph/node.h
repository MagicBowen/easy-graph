#ifndef HF37ACE88_F726_4AA3_8599_ED7A888AA623
#define HF37ACE88_F726_4AA3_8599_ED7A888AA623

#include "easy_graph/graph/node_id.h"
#include "easy_graph/infra/operator.h"
#include "easy_graph/graph/subgraph.h"
#include "easy_graph/attribute/attributes_mixin.h"
#include "easy_graph/graph/box.h"
#include <vector>

EG_NS_BEGIN

struct SubgraphVisitor;

struct Node : AttributesMixin
{
	Node(const NodeId&);

    __DECL_COMP(Node);

    NodeId getId() const;

    Node& packing(const BoxPtr&);

    template<typename ANYTHING>
    ANYTHING* unpacking() const {
    	if(!box) return nullptr;
    	return box_unpacking<ANYTHING>(box);
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
