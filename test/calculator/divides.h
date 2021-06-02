#ifndef HF4A3278E_2D68_4741_8501_C8D0514A8D7F
#define HF4A3278E_2D68_4741_8501_C8D0514A8D7F

#include "easy_graph/graph/box.h"
#include "calculator/integer.h"
#include "calculator/id_generator.h"
#include <string>

EG_NS_BEGIN

struct Divides : Box {
	Integer operator()(Integer lhs, Integer rhs) {
		return Integer(int(lhs.getValue() / rhs.getValue()));
	}

private:
	NodeId getId() const override {
		return std::string("divides_") + std::to_string(IdGenerator::getInstance().generate());
	}
};

EG_NS_END

#endif
