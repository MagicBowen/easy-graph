#ifndef H9121AF36_31A3_4E9C_957D_F41FF81BE7E3
#define H9121AF36_31A3_4E9C_957D_F41FF81BE7E3

#include <cctest/cctest.h>
#include "easy_graph/builder/box_builder.h"
#include "anything/calculator.h"
#include "anything/candy.h"

EG_NS_BEGIN

FIXTURE(BoxTest) {
	TEST("box packing and unpacking") {
		auto box = box_packing<Integer>(5);

		auto nonething = box_unpacking<Plus>(box);
		ASSERT_FALSE(nonething);

		auto anything = box_unpacking<Integer>(box);
		ASSERT_TRUE(anything);
		ASSERT_EQ(5, anything->getValue());
	}

	TEST("box_of subclass") {
		auto box = BOX_OF(Integer, 3);

		auto anything = box_unpacking<Integer>(box);
		ASSERT_TRUE(anything);
		ASSERT_EQ(3, anything->getValue());
	}

	TEST("box_of any class") {
		auto box = BOX_OF(JellyCandy, JellyCandy::CIRCLE);
		auto anything = box_unpacking<Candy>(box);
		ASSERT_TRUE(anything);
		ASSERT_EQ(std::string("Jelly (Shape:Circle)"), anything->getLabel());
	}
};

EG_NS_END

#endif
