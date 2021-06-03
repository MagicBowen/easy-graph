#ifndef HF99FEC83_103E_4A0E_B645_2ECA001F73F9
#define HF99FEC83_103E_4A0E_B645_2ECA001F73F9

#include "easy_graph/graph/box.h"
#include "easy_graph/infra/operator.h"

EG_NS_BEGIN

///////////////////////////////////////////////////////////////
struct Integer : Box {
	explicit Integer(int value)
	: value(value) {
	}

	__INLINE_EQUALS(Integer) {
		return this->value == rhs.value;
	}

	int getValue() const {
		return value;
	}

private:
	int value{0};
};

///////////////////////////////////////////////////////////////
INTERFACE(Operator) {
	ABSTRACT(Integer operator()(const Integer& lhs, const Integer& rhs));
};

///////////////////////////////////////////////////////////////
struct Plus : Operator, Box {
private:
	Integer operator()(const Integer& lhs, const Integer& rhs) override {
		return Integer(lhs.getValue() + rhs.getValue());
	}
};

///////////////////////////////////////////////////////////////
struct Minus : Operator, Box {
private:
	Integer operator()(const Integer& lhs, const Integer& rhs) override {
		return Integer(lhs.getValue() - rhs.getValue());
	}
};

///////////////////////////////////////////////////////////////
struct Multiplies : Operator, Box {
private:
	Integer operator()(const Integer& lhs, const Integer& rhs) override {
		return Integer(lhs.getValue() * rhs.getValue());
	}
};

///////////////////////////////////////////////////////////////
struct Divides : Operator, Box {
private:
	Integer operator()(const Integer& lhs, const Integer& rhs) override {
		return Integer(int(lhs.getValue() / rhs.getValue()));
	}
};

EG_NS_END

#endif
