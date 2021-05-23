#ifndef HF37ACE88_F726_4AA3_8599_ED7A888AA623
#define HF37ACE88_F726_4AA3_8599_ED7A888AA623

#include "node_id.h"
#include "cmp_helper.h"

EG_NS_BEGIN

struct Node {
    explicit Node(const NodeId& id);
    Node(const char* id);

    __DECL_COMP(Node);

    NodeId getId() const;
    std::string getLayout() const;

private:
    NodeId id;
};

EG_NS_END

#endif
