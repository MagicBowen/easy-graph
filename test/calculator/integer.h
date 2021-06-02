#ifndef H0F4D718C_898D_485A_A9C5_92C634033A6E
#define H0F4D718C_898D_485A_A9C5_92C634033A6E

#include <string>

EG_NS_BEGIN

struct Integer {
	explicit Integer(int value) : value(value) {
	}

	int getValue() const {
		return value;
	}

private:
	int value{0};
};

EG_NS_END

#endif
