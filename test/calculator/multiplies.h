#ifndef H7E81123F_AF2B_4EB7_955E_D01F3B0E18CB
#define H7E81123F_AF2B_4EB7_955E_D01F3B0E18CB

#include "calculator/integer.h"

EG_NS_BEGIN

struct Multiplies {
	Integer operator()(Integer lhs, Integer rhs) {
		return Integer(lhs.getValue() * rhs.getValue());
	}
};

EG_NS_END

#endif
