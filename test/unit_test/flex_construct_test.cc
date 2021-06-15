#include <cctest/cctest.h>
#include <type_traits>
#include <string>
#include <vector>

namespace {
	struct FlexConstructor {
		template<typename ... TS>
		FlexConstructor(TS && ...ts) {
			classify(std::forward<TS>(ts)...);
		}

		template<typename T, typename ...TS>
		void classify(T && t, TS && ...ts) {
			if constexpr (std::is_same_v<std::string, std::decay_t<T>>) {
				strings.push_back(std::forward<T>(t));

			} else if constexpr (std::is_same_v<int, std::decay_t<T>>) {
				numbers.push_back(std::forward<T>(t));

			} else {
				static_assert(!sizeof(T), "unsupported construction type!");
			}

			if constexpr (sizeof...(TS) > 0) {
				classify(std::forward<TS>(ts)...);
			}
		}

		std::vector<int> numbers;
		std::vector<std::string> strings;
	};
}

FIXTURE(FlexConstructorTest) {
	TEST("should classify construction parameters by specified types") {
		FlexConstructor fc{1, std::string("hello"), 2, std::string("world"), 3};

		ASSERT_EQ(3, fc.numbers.size());
		ASSERT_EQ(1, fc.numbers[0]);
		ASSERT_EQ(2, fc.numbers[1]);
		ASSERT_EQ(3, fc.numbers[2]);

		ASSERT_EQ(2, fc.strings.size());
		ASSERT_EQ("hello", fc.strings[0]);
		ASSERT_EQ("world", fc.strings[1]);
    }
};
