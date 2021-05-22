#ifndef H82BFAF0B_FC11_4BF4_878C_44AED5305793
#define H82BFAF0B_FC11_4BF4_878C_44AED5305793

#include "easy_graph/eg.h"
#include "keywords.h"

EG_NS_BEGIN

struct Edge;

INTERFACE(EdgeVisitor) {
	ABSTRACT(void visit(const Edge&));
};

EG_NS_END

#endif
