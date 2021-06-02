#ifndef H8FACBE3D_1D3F_461E_A963_76142FE7EEDA
#define H8FACBE3D_1D3F_461E_A963_76142FE7EEDA

#include "calculator/integer.h"

EG_NS_BEGIN

struct Minus {
	Integer operator()(Integer lhs, Integer rhs) {
		return Integer(lhs.getValue() - rhs.getValue());
	}
};

EG_NS_END

#endif
