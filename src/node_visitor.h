#ifndef H985962DA_9DE8_4771_9A0E_E6A07EC60367
#define H985962DA_9DE8_4771_9A0E_E6A07EC60367

#include "easy_graph/eg.h"
#include "keywords.h"

EG_NS_BEGIN

struct Node;

INTERFACE(NodeVisitor) {
	ABSTRACT(void visit(const Node&));
};

EG_NS_END

#endif
