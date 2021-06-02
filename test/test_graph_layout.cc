#include <cctest/cctest.h>

#include "easy_graph/builder/graph_dsl.h"

#include "calculator/plus.h"
#include "calculator/minus.h"
#include "calculator/multiplies.h"
#include "calculator/divides.h"

#include "easy_graph/layout/graph_layout.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_executor.h"

EG_NS_BEGIN

FIXTURE(GraphLayoutTest) {
	GraphEasyExecutor executor;

	BEFORE {
		GraphLayout::getInstance().config(executor);
	}

	TEST("should calculate caculator graph success") {

		// (5+2)*3 - (8/2)
		GRAPH(graph) {
			NODE(plus, Plus);
			NODE(minus, Minus);
			NODE(multi, Multiplies);
			NODE(div, Divides);

			CHAIN(Node("5", Integer(5)) -> Node(plus) -> Node(multi) -> Node(minus));
			CHAIN(Node("2", Integer(2)) -> Node(plus));
			CHAIN(Node("3", Integer(3)) -> Node(multi));
			CHAIN(Node("8", Integer(8)) -> Node(div) -> Node(minus));
			CHAIN(Node("data(2)", Integer(2)) -> Node(div));
		});

//		auto node = graph.findNode("plus");
//		ASSERT_TRUE(node);
//
//		auto n1 = graph.findNode("5");
//		ASSERT_TRUE(n1);
//
//		auto n2 = graph.findNode("2");
//		ASSERT_TRUE(n2);
//
//		auto l1 = n1->unpacking<Integer>();
//		ASSERT_TRUE(l1);
//
//		auto l2 = n2->unpacking<Integer>();
//		ASSERT_TRUE(l2);
//
//		auto op = node->unpacking<Plus>();
//		ASSERT_EQ(7, (*op)(*l1, *l2).getValue());

		ASSERT_TRUE(__EG_OK(graph.layout()));
	}
};

EG_NS_END
