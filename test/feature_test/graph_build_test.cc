#include <cctest/cctest.h>
#include "easy_graph/builder/graph_dsl.h"
#include "anything/calculator.h"

USING_EG_NS

FIXTURE(GraphBuildTest) {

	GRAPH(calculator) {
		Node plus("plus", BOX_OF(Plus), Attributes{{"danger", false}, {"input", 2}});
		Node minus("minus", BOX_OF(Minus));
		Node i1("2", BOX_OF(Integer, 2));
		Node i2("5", BOX_OF(Integer, 5));

		CHAIN(Node(i1) -> Node(plus) -> Node(minus) -> Node("div", BOX_OF(Divides)));
		CHAIN(Node(i2) -> Node(plus));
		CHAIN(Node("3", BOX_OF(Integer, 3), Attribute{"const", true}) -> Node(minus));
		CHAIN(Node(i1) -> Node("div"));
	});

	TEST("should get none box when node not in graph") {
		auto multi = calculator.findNode("multi");
		ASSERT_FALSE(multi);
	}

	TEST("should get box when node in graph") {
		auto n1 = calculator.findNode("5");
		ASSERT_TRUE(n1);
	}

	TEST("should unpacking thing from box") {
		auto n1 = calculator.findNode("5");
		auto i1 = n1->unpacking<Integer>();
		ASSERT_TRUE(i1);
		ASSERT_EQ(5, i1->getValue());
	}

	TEST("should unpacking interface from box") {
		auto plus = calculator.findNode("plus");
		auto op = plus->unpacking<Operator>();
		ASSERT_TRUE(op);
	}

	TEST("should invoke interface from box") {
		auto n1 = calculator.findNode("5");
		auto i1 = n1->unpacking<Integer>();

		auto n2 = calculator.findNode("2");
		auto i2 = n2->unpacking<Integer>();

		auto plus = calculator.findNode("plus");
		auto op = plus->unpacking<Operator>();

		ASSERT_EQ(Integer(7), (*op)(*i1, *i2));
	}

	TEST("should invoke interface from box of multiple nodes") {
		auto n1 = calculator.findNode("5");
		auto i1 = n1->unpacking<Integer>();

		auto n2 = calculator.findNode("2");
		auto i2 = n2->unpacking<Integer>();


		auto div = calculator.findNode("div");
		auto op = div->unpacking<Operator>();

		ASSERT_EQ(Integer(2), (*op)(*i1, *i2));
	}

	TEST("should get attribute from node") {
		auto n = calculator.findNode("3");

		auto attr = n->getAttr<bool>("const");
		ASSERT_TRUE(attr);
		ASSERT_TRUE(*attr);
	}

	TEST("should get none attribute from node with wrong key") {
		auto n = calculator.findNode("3");

		auto attr = n->getAttr<bool>("constant");
		ASSERT_FALSE(attr);
	}

	TEST("should get none attribute from node with wrong type") {
		auto n = calculator.findNode("3");

		auto attr = n->getAttr<int>("const");
		ASSERT_FALSE(attr);
	}

	TEST("should get attributes from node") {
		auto n = calculator.findNode("plus");

		auto danger = n->getAttr<bool>("danger");
		ASSERT_TRUE(danger);
		ASSERT_FALSE(*danger);

		auto input = n->getAttr<int>("input");
		ASSERT_TRUE(input);
		ASSERT_EQ(2, *input);
	}
};
