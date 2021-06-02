#ifndef H7E81123F_AF2B_4EB7_955E_D01F3B0E18CB
#define H7E81123F_AF2B_4EB7_955E_D01F3B0E18CB

#include "easy_graph/graph/box.h"
#include "calculator/integer.h"
#include "calculator/id_generator.h"
#include <string>

EG_NS_BEGIN

struct Multiplies : Box {
	Integer operator()(Integer lhs, Integer rhs) {
		return Integer(lhs.getValue() * rhs.getValue());
	}

private:
	NodeId getId() const override {
		return std::string("multiplies_") + std::to_string(IdGenerator::getInstance().generate());
	}
};

EG_NS_END

#endif
