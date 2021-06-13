#ifndef H19D3F004_119F_4E6A_ACFA_A635FD6FEA98
#define H19D3F004_119F_4E6A_ACFA_A635FD6FEA98

#include "easy_graph/infra/keywords.h"
#include "easy_graph/infra/operator.h"

EG_NS_BEGIN

INTERFACE(EdgeType) {
	static EdgeType& CTRL();
	static EdgeType& DATA();

	__DECL_COMP(EdgeType);
};

EG_NS_END

#endif
