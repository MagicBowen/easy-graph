#ifndef HC7104B0D_28EB_485F_8CE2_59187896F0F3
#define HC7104B0D_28EB_485F_8CE2_59187896F0F3

#include "easy_graph/infra/keywords.h"
#include "easy_graph/graph/attribute.h"

EG_NS_BEGIN

INTERFACE(AttributeVisitor) {
	ABSTRACT(void visit(const Attribute&));
};


EG_NS_END

#endif
