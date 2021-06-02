#ifndef H2C489ACD_950A_4349_9A5E_D36096D09266
#define H2C489ACD_950A_4349_9A5E_D36096D09266

#include "easy_graph/graph/box.h"
#include "calculator/integer.h"
#include "calculator/id_generator.h"
#include <string>

EG_NS_BEGIN

struct Plus : Box {
	Integer operator()(Integer lhs, Integer rhs) {
		return Integer(lhs.getValue() + rhs.getValue());
	}

private:
	NodeId getId() const override {
		return std::string("plus_") + std::to_string(IdGenerator::getInstance().generate());
	}
};

EG_NS_END

#endif
