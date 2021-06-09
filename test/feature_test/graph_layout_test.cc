#include <cctest/cctest.h>
#include "easy_graph/builder/graph_dsl.h"
#include "easy_graph/layout/graph_layout.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_executor.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "anything/calculator.h"
#include "anything/candy.h"

USING_EG_NS

FIXTURE(GraphLayoutTest) {
	GraphEasyExecutor executor;
	GraphEasyOption options;

	BEFORE {
		options.format = LayoutFormat::BOXART;
	    options.output = LayoutOutput::CONSOLE;
		options.dir = FlowDir::LR;
		options.type = LayoutType::FREE;
		options.scale = 1;

		GraphLayout::getInstance().config(executor, &options);
	}

	TEST("should layout calculator graph") {
		GRAPH(calculator) {
			Node i1("2", BOX_OF(Integer, 2));
			Node i2("5", BOX_OF(Integer, 5));

			CHAIN(Node("2") -> Node("plus", BOX_OF(Plus)) -> Node("minus", BOX_OF(Minus)) -> Node("div", BOX_OF(Divides)));
			CHAIN(Node("5") -> Node("plus"));
			CHAIN(Node("3", BOX_OF(Integer, 3)) -> Node("minus"));
			CHAIN(Node("2") -> Node("div"));
		});

		ASSERT_TRUE(__EG_OK(calculator.layout()));
	}

	TEST("should layout candy graph") {
		GRAPH(c1, "dove candy") {
			CHAIN(Node("dove", BOX_OF(ToffeeCandy, "Dove")) -> Node("sweet", BOX_OF(HardCandy, 5)));
		});

		GRAPH(c2, "circle candy") {
			CHAIN(Node("circle", BOX_OF(JellyCandy, JellyCandy::CIRCLE)) -> Node("rainbow", BOX_OF(ColorCandy, 3, 2, 1)));
		});

		GRAPH(candy) {
			Node jelly{"jelly",  BOX_OF(JellyCandy, JellyCandy::CIRCLE), c1, c2};
			Node rainbow{"rainbow", BOX_OF(ColorCandy, 3, 2, 1)};

			CHAIN(Node("dove", BOX_OF(ToffeeCandy, "Dove")) -> Node(jelly) -> Node("sweet", BOX_OF(HardCandy, 3)));
			CHAIN(Node("dove") -> Node(rainbow) -> Node("toffee", BOX_OF(ToffeeCandy, "Haribo"), c2, c1));
		});

		ASSERT_TRUE(__EG_OK(c1.layout()));
		ASSERT_TRUE(__EG_OK(c2.layout()));
		ASSERT_TRUE(__EG_OK(candy.layout()));
	}
};
