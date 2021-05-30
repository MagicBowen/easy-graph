#ifndef HE94B7115_08E9_4FD2_BA18_D61FAEA02902
#define HE94B7115_08E9_4FD2_BA18_D61FAEA02902

#include "easy_graph/infra/keywords.h"
#include "easy_graph/graph/node_id.h"

EG_NS_BEGIN

INTERFACE(Box) {
	ABSTRACT(NodeId getId() const);
};

EG_NS_END

#endif
