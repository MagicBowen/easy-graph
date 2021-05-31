#include <cctest/cctest.h>
#include "easy_graph/builder/graph_dsl.h"
#include "easy_graph/layout/graph_layout.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_executor.h"
#include "candy/candy_box.h"
#include "candy/integer.h"
#include "candy/shape.h"
#include "candy/color.h"

USING_EG_NS

FIXTURE(GraphLayoutTest) {
	GraphEasyExecutor executor;

	BEFORE {
		GraphLayout::getInstance().config(executor);
	}

	TEST("should layout candy graph success") {
		GRAPH(g1) {
			Node i1{CANDY(Integer, 1)};
			Node s1{CANDY(Shape, ShapeType::RECT)};
			Node c1{CANDY(Color, 100, 128, 223)};

			CHAIN(NODE(i1) -> NODE(s1) -> NODE(c1));
			CHAIN(NODE(i1) -> CANDY_NODE(Shape, ShapeType::CIRCLE));
			CHAIN(CANDY_NODE(Shape, ShapeType::CIRCLE) -> CANDY_NODE(Color, 100, 128, 223));
		});

		ASSERT_TRUE(__EG_OK(g1.layout()));
	}
};
