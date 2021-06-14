#ifndef HCD125EDA_687E_4E91_AC99_99F3F8880CC6
#define HCD125EDA_687E_4E91_AC99_99F3F8880CC6

#include "easy_graph/infra/keywords.h"

EG_NS_BEGIN

struct InputWire;
struct OutputWire;

INTERFACE(WireVisitor) {
	ABSTRACT(void visit(const InputWire&));
	ABSTRACT(void visit(const OutputWire&));
};

EG_NS_END

#endif
