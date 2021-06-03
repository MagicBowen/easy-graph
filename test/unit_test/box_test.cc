#ifndef H9121AF36_31A3_4E9C_957D_F41FF81BE7E3
#define H9121AF36_31A3_4E9C_957D_F41FF81BE7E3

#include <cctest/cctest.h>
#include "easy_graph/builder/box_builder.h"
#include "anything/calculator.h"
#include "anything/candy.h"

EG_NS_BEGIN

FIXTURE(BoxTest) {
	TEST("box unpacking nothing") {
		auto box = box_packing<Integer>(5);
		auto nonething = box_unpacking<Plus>(box);
		ASSERT_FALSE(nonething);
	}

	TEST("box unpacking something") {
		auto box = box_packing<Integer>(5);
		auto something = box_unpacking<Integer>(box);

		ASSERT_TRUE(something);
		ASSERT_EQ(5, something->getValue());
	}

	TEST("box unpacking interface") {
		auto box = BOX_OF(JellyCandy, JellyCandy::CIRCLE);
		auto candy = box_unpacking<Candy>(box);
		ASSERT_TRUE(candy);
		ASSERT_EQ(std::string("Jelly (Shape:Circle)"), candy->getLabel());
	}
};

EG_NS_END

#endif
