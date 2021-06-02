#ifndef H8FACBE3D_1D3F_461E_A963_76142FE7EEDA
#define H8FACBE3D_1D3F_461E_A963_76142FE7EEDA

#include "easy_graph/graph/box.h"
#include "calculator/integer.h"
#include "calculator/id_generator.h"
#include <string>

EG_NS_BEGIN

struct Minus : Box {
	Integer operator()(Integer lhs, Integer rhs) {
		return Integer(lhs.getValue() - rhs.getValue());
	}

private:
	NodeId getId() const override {
		return std::string("minus_") + std::to_string(IdGenerator::getInstance().generate());
	}
};

EG_NS_END

#endif
