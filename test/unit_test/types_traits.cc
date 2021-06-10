#include <cctest/cctest.h>
#include "easy_graph/eg.h"
#include <type_traits>

//USING_EG_NS

namespace {
//	template<typename ...TS>
//	void classifyByType(TS && ...ts) {
//		using T = std::decay<decltype(ts)>;
//
//		if constexpr
//	}
}

FIXTURE(TypesTraitsTest) {
	TEST("should success") {
        ASSERT_TRUE(true);
    }
};
