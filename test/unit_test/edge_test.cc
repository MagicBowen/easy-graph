#include <cctest/cctest.h>
#include "easy_graph/builder/edge_builder.h"
#include <set>

USING_EG_NS

FIXTURE(EdgeCompareTest) {
	TEST("edges are equal when src && dst && type are all equal") {
		ASSERT_TRUE(edge_of("a", "b") == edge_of("a", "b"));
	}

	TEST("edges are not equal when src or dst are not equal") {
		ASSERT_FALSE(edge_of("a", "b") == edge_of("a", "c"));
	}

	TEST("edges are not equal when types are not equal") {
		ASSERT_FALSE(edge_of("a", "b", ctrl_edge()) == edge_of("a", "b", data_edge()));
	}
};

FIXTURE(EdgeSetTest) {
	std::set<Edge> edges;

	AFTER {
		edges.clear();
	}

	TEST("should insert edges with different endpoints in set") {
		edges.emplace(edge_of("a", "b", data_edge()));
		edges.emplace(edge_of(ep_of("a"), ep_of("b", 1)));
		ASSERT_EQ(2, edges.size());
	}

	TEST("should insert edges with different types in set") {
		edges.emplace(edge_of("a", "b", data_edge()));
		edges.emplace(edge_of("a", "b", ctrl_edge()));
		ASSERT_EQ(2, edges.size());
	}
};
