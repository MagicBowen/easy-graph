#include <cctest/cctest.h>
#include "easy_graph/infra/macro_traits.h"

USING_EG_NS

FIXTURE(MacroTraitsTest) {
	TEST("va_args length") {
		ASSERT_EQ(0, VA_ARGS_NUM());
		ASSERT_EQ(1, VA_ARGS_NUM(1));
		ASSERT_EQ(2, VA_ARGS_NUM(a, b));
		ASSERT_EQ(3, VA_ARGS_NUM(1, 2, 3));
		ASSERT_EQ(4, VA_ARGS_NUM(a, b, c, d));
		ASSERT_EQ(5, VA_ARGS_NUM(1, 2, 3, 4, 5));
		ASSERT_EQ(6, VA_ARGS_NUM(1, 2, 3, 4, 5, e));
	}

	TEST("if by false condition") {
		auto result = MACRO_CONDITION(0)("true path", "false path");
		ASSERT_EQ(std::string("false path"), result);
	}

	TEST("if by true condition") {
		auto result = MACRO_CONDITION(3)("true path", "false path");
		ASSERT_EQ(std::string("true path"), result);
	}

	TEST("if by va_args length eaual to 0") {
		auto result = MACRO_CONDITION(VA_ARGS_NUM())("true path", "false path");
		ASSERT_EQ(std::string("false path"), result);
	}

	TEST("if by va_args length greater than 0") {
		auto result = MACRO_CONDITION(VA_ARGS_NUM(a, b))("true path", "false path");
		ASSERT_EQ(std::string("true path"), result);
	}
};
