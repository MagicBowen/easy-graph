#ifndef H2C489ACD_950A_4349_9A5E_D36096D09266
#define H2C489ACD_950A_4349_9A5E_D36096D09266

#include "calculator/integer.h"

EG_NS_BEGIN

struct Plus {
	Integer operator()(Integer lhs, Integer rhs) {
		return Integer(lhs.getValue() + rhs.getValue());
	}
};

EG_NS_END

#endif
