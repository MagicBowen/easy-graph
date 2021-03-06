#ifndef HEA57C9F8_DA90_4F2F_966C_229452FA8578
#define HEA57C9F8_DA90_4F2F_966C_229452FA8578

#include "easy_graph/infra/keywords.h"

EG_NS_BEGIN

struct Subgraph;

INTERFACE(SubgraphVisitor) {
	ABSTRACT(void visit(const Subgraph&));
};

EG_NS_END


#endif
