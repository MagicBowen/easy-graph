#include <cctest/cctest.h>

#include "easy_graph/builder/graph_dsl.h"

#include "calculator/plus.h"
#include "calculator/minus.h"
#include "calculator/multiplies.h"
#include "calculator/divides.h"

#include "easy_graph/layout/graph_layout.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_executor.h"

EG_NS_BEGIN

FIXTURE(GraphBoxTest) {
	GraphEasyExecutor executor;

	BEFORE {
		GraphLayout::getInstance().config(executor);
	}

	TEST("should calculate caculator graph success") {

		// (5+2)*3 - (8/2)
		GRAPH(graph) {

			Node plus("plus", Plus{});
			Node minus("minus", Minus{});
			Node multi("multi", Multiplies{});
			Node div("div", Divides{});

			CHAIN(Node("5", Integer(5)) -> Node(plus) -> Node(multi) -> Node(minus));
			CHAIN(Node("2", Integer(2)) -> Node(plus));
			CHAIN(Node("3", Integer(3)) -> Node(multi));
			CHAIN(Node("8", Integer(8)) -> Node(div) -> Node(minus));
			CHAIN(Node("data(2)", Integer(2)) -> Node(div));
		});

		ASSERT_TRUE(__EG_OK(graph.layout()));
	}
};

EG_NS_END
