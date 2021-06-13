#ifndef HCD125EDA_687E_4E91_AC99_99F3F8880CC6
#define HCD125EDA_687E_4E91_AC99_99F3F8880CC6

#include "easy_graph/infra/keywords.h"

EG_NS_BEGIN

struct Wire;

INTERFACE(WireVisitor) {
	ABSTRACT(void visitInput(const Wire&));
	ABSTRACT(void visitOutput(const Wire&));
};

EG_NS_END

#endif
