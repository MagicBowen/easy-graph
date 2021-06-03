#include <cctest/cctest.h>

#include "easy_graph/builder/graph_dsl.h"
#include "easy_graph/layout/graph_layout.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_executor.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "anything/candy.h"
#include "anything/calculator.h"

EG_NS_BEGIN

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

	TEST("should layout calculator graph success") {
		GRAPH(calculator) {
			Node plus("plus", BOX_OF(Plus));
			Node minus("minus", BOX_OF(Minus));
			Node i1("2", BOX_OF(Integer, 2));
			Node i2("5", BOX_OF(Integer, 5));

			CHAIN(Node(i1) -> Node(plus) -> Node(minus) -> Node("div", BOX_OF(Divides)));
			CHAIN(Node(i2) -> Node(plus));
			CHAIN(Node("3", BOX_OF(Integer, 3)) -> Node(minus));
			CHAIN(Node(i1) -> Node("div", BOX_OF(Divides)));
		});

		ASSERT_TRUE(__EG_OK(calculator.layout()));
	}

	TEST("should layout candy graph success") {
		GRAPH(c1) {
			CHAIN(Node("dove", BOX_OF(ToffeeCandy, "Dove")) -> Node("sweet", BOX_OF(HardCandy, 5)));
		});

		GRAPH(c2) {
			CHAIN(Node("circle", BOX_OF(JellyCandy, JellyCandy::CIRCLE)) -> Node("rainbow", BOX_OF(ColorCandy, 3, 2, 1)));
		});

		GRAPH(candy) {
			Node dove{"dove", BOX_OF(ToffeeCandy, "Dove")};
			Node jelly{"jelly",  BOX_OF(JellyCandy, JellyCandy::CIRCLE), c1, c2};
			Node rainbow{"rainbow", BOX_OF(ColorCandy, 3, 2, 1)};

			CHAIN(Node(dove) -> Node(jelly) -> Node("sweet", BOX_OF(HardCandy, 3)));
			CHAIN(Node(dove) -> Node(rainbow) -> Node("toffee", BOX_OF(ToffeeCandy, "Haribo"), c2, c1));
		});

		ASSERT_TRUE(__EG_OK(c1.layout()));
		ASSERT_TRUE(__EG_OK(c2.layout()));
		ASSERT_TRUE(__EG_OK(candy.layout()));
	}
};

EG_NS_END
