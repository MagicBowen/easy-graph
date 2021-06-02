#include <cctest/cctest.h>

#include "easy_graph/builder/graph_dsl.h"
#include "easy_graph/layout/graph_layout.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_executor.h"

#include "candy/candy_box.h"
#include "candy/hard_candy.h"
#include "candy/jelly_candy.h"
#include "candy/color_candy.h"
#include "candy/toffee_candy.h"

USING_EG_NS

FIXTURE(GraphLayoutTest) {
	GraphEasyExecutor executor;

	BEFORE {
		GraphLayout::getInstance().config(executor);
	}

	TEST("should layout candy graph success") {
		GRAPH(g1) {
			CHAIN(Node("a") -> Node("b"));
		});

		GRAPH(g2) {
			CHAIN(Node("a") -> Node("b") -> Node("c"));
		});

		GRAPH(graph) {
			Node h1{CANDY(HardCandy, 1)};
			Node j1{CANDY(JellyCandy, JellyType::TRIANGLE)};
			Node c1{CANDY(ColorCandy, 100, 128, 223)};
			Node l1{CANDY(ToffeeCandy, "Dove"), g1};

			CHAIN(Node(h1) -> Node(j1) -> Node(CANDY(ColorCandy, 100, 128, 223), g1, g2) -> Node(l1));
			CHAIN(Node(h1) -> Node(CANDY(JellyCandy, JellyType::CIRCLE)) -> Node(l1));
			CHAIN(Node(CANDY(JellyCandy, JellyType::CIRCLE)) -> Node(CANDY(ColorCandy, 100, 128, 223)));
		});

		ASSERT_TRUE(__EG_OK(graph.layout()));
	}
};
