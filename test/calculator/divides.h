#ifndef HF4A3278E_2D68_4741_8501_C8D0514A8D7F
#define HF4A3278E_2D68_4741_8501_C8D0514A8D7F

#include "calculator/integer.h"

EG_NS_BEGIN

struct Divides {
	Integer operator()(Integer lhs, Integer rhs) {
		return Integer(int(lhs.getValue() / rhs.getValue()));
	}
};

EG_NS_END

#endif
