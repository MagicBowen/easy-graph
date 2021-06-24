#include <cctest/cctest.h>
#include "easy_graph/layout/engines/graph_easy/graph_easy_layout_engine.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"
#include "easy_graph/layout/graph_layout.h"
#include "easy_graph/builder/graph_dsl.h"
#include "easy_graph/infra/status.h"
#include "anything/calculator.h"
#include "anything/candy.h"

USING_EG_NS

FIXTURE(GraphLayoutTest) {
	GraphEasyLayoutEngine executor;
	GraphEasyOption options;

	BEFORE {
		options.format = LayoutFormat::BOXART;
	    options.output = LayoutOutput::CONSOLE;
		options.dir = FlowDir::LR;
		options.type = LayoutType::FREE;
		options.scale = 1;

		GraphLayout::getInstance().config(executor, &options);
	}

	AFTER {
		GraphLayout::getInstance().reset();
	}

	TEST("should layout calculator graph") {
		GRAPH(calculator) {
			auto i1 = node_of("2", box_of<Integer>(2));
			auto i2 = node_of("5", box_of<Integer>(5));

			CHAIN(Node("2") -> Node("plus", box_of<Plus>())) -> Node("minus", box_of<Minus>()) -> Node("div", box_of<Divides>());
			CHAIN(Node("5") -> Node("plus"));
			CHAIN(Node("3", box_of<Integer>(3)) -> Node("minus"));
			CHAIN(Node("2") -> Node("div"));
		};

		ASSERT_TRUE(eg_status_ok(calculator.layout()));
	}

	TEST("should layout candy graph") {
		GRAPH(c1) {
			CHAIN(Node("dove", box_of<ToffeeCandy>("Dove")) -> Node("sweet", box_of<HardCandy>(5)));
		};

		GRAPH(c2) {
			CHAIN(Node("circle", box_of<JellyCandy>(JellyShape::CIRCLE)) -> Node("rainbow", box_of<ColorCandy>(3, 2, 1)));
		};

		GRAPH(candy) {
			HAS_NODE(jelly,   box_of<JellyCandy>(JellyShape::CIRCLE), subgraph_of(c1,"dove"), subgraph_of(c2,"circle"));
			HAS_NODE(rainbow, box_of<ColorCandy>(3, 2, 1));

			CHAIN(Node("dove", box_of<ToffeeCandy>("Dove")) -> Node(jelly) -> Node("sweet", box_of<HardCandy>(3)));
			CHAIN(Node("dove") -> Node(rainbow) -> Node("toffee", box_of<ToffeeCandy>("Haribo"), subgraph_of(c2), subgraph_of(c1)));
		};

		ASSERT_TRUE(eg_status_ok(c1.layout()));
		ASSERT_TRUE(eg_status_ok(c2.layout()));
		ASSERT_TRUE(eg_status_ok(candy.layout()));
	}
};
