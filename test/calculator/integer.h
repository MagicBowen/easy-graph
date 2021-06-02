#ifndef H0F4D718C_898D_485A_A9C5_92C634033A6E
#define H0F4D718C_898D_485A_A9C5_92C634033A6E

#include "easy_graph/graph/box.h"
#include "calculator/id_generator.h"
#include <string>

EG_NS_BEGIN

struct Integer : Box {
	Integer(int value) : value(value) {
	}

	int getValue() const {
		return value;
	}

private:
	NodeId getId() const override {
		return std::string("integer_") + std::to_string(IdGenerator::getInstance().generate()) + "(" + std::to_string(value) + ")";
	}

private:
	int value{0};
};

EG_NS_END

#endif
