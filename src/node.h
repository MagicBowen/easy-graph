#ifndef HF37ACE88_F726_4AA3_8599_ED7A888AA623
#define HF37ACE88_F726_4AA3_8599_ED7A888AA623

#include "node_id.h"
#include "cmp_helper.h"
#include "layoutable.h"
#include <vector>

EG_NS_BEGIN

struct Graph;

struct Node  : Layoutable
{
    explicit Node(const NodeId& id);
    Node(const char* id);

    template<typename ...GRAPHS>
    Node(const NodeId& id, const GRAPHS&... graphs)
	: id(id), subgraphs{&graphs...}{
    }

    __DECL_COMP(Node);

    NodeId getId() const;

private:
    std::string getLayout(const LayoutContext&) const override;

private:
    NodeId id;
    std::vector<const Graph*> subgraphs;
};

EG_NS_END

#endif
