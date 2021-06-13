#ifndef H19D3F004_119F_4E6A_ACFA_A635FD6FEA98
#define H19D3F004_119F_4E6A_ACFA_A635FD6FEA98

#include "easy_graph/infra/keywords.h"
#include "easy_graph/infra/operator.h"
#include <string>

EG_NS_BEGIN

struct GraphEasyEdgeLayout;
struct GraphEasyLayoutContext;
struct Edge;

INTERFACE(AutoLinkPortTrait) {
};

INTERFACE(GraphEasyEdgeLayoutTrait) {
	ABSTRACT(std::string getAttrLayout(const Edge&, GraphEasyLayoutContext&) const);
	ABSTRACT(std::string getArrowLayout(const Edge&, GraphEasyLayoutContext&) const);
};

INTERFACE(EdgeType) {
	static EdgeType& CTRL();
	static EdgeType& DATA();

	__DECL_COMP(EdgeType);
};

template<typename Trait>
const Trait* edge_type_trait_cast(const EdgeType& type) {
	return dynamic_cast<const Trait*>(&type);
}

EG_NS_END

#endif
