#include <cctest/cctest.h>
#include "easy_graph/builder/graph_dsl.h"
#include "anything/calculator.h"

EG_NS_BEGIN

FIXTURE(GraphBuildTest) {
	TEST("should get the boxed thing in node") {
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

		auto multi = calculator.findNode("multi");
		ASSERT_FALSE(multi);

		auto n1 = calculator.findNode("2");
		ASSERT_TRUE(n1);

		auto i1 = n1->unpacking<Integer>();
		ASSERT_TRUE(i1);
		ASSERT_EQ(2, i1->getValue());

		auto n2 = calculator.findNode("5");
		ASSERT_TRUE(n2);

		auto i2 = n2->unpacking<Integer>();
		ASSERT_TRUE(i2);
		ASSERT_EQ(5, i2->getValue());

		auto plus = calculator.findNode("plus");
		ASSERT_TRUE(plus);

		auto op = plus->unpacking<Operator>();
		ASSERT_TRUE(op);
		ASSERT_EQ(Integer(7), (*op)(*i1, *i2));
	}
};

EG_NS_END
