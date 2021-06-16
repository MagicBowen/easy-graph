#include <cctest/cctest.h>
#include "easy_graph/builder/box_builder.h"
#include "anything/calculator.h"
#include "anything/candy.h"

USING_EG_NS

FIXTURE(BoxTest) {
	TEST("box unpacking nothing") {
		auto box = box_packing<Integer>(5);
		auto nonething = box_unpacking<Plus>(box);
		ASSERT_FALSE(nonething);
	}

	TEST("box unpacking something inherited box") {
		auto box = box_packing<Integer>(5);
		auto something = box_unpacking<Integer>(box);

		ASSERT_TRUE(something);
		ASSERT_EQ(5, something->getValue());
	}

	TEST("box unpacking something not inherited from box") {
		auto box = box_packing<box_wrapper<ToffeeCandy>>("Dove");
		auto something = box_unpacking<ToffeeCandy>(box);

		ASSERT_TRUE(something);
		ASSERT_EQ("Toffee (Label:Dove)", static_cast<Candy*>(something)->getLabel());
	}

	TEST("box unpacking interface") {
		auto box = box_of<JellyCandy>(JellyShape::CIRCLE);
		auto candy = box_unpacking<Candy>(box);
		ASSERT_TRUE(candy);
		ASSERT_EQ("Jelly (Shape:Circle)", candy->getLabel());
	}
};
