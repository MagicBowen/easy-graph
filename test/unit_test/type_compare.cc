#include <cctest/cctest.h>
#include "easy_graph/infra/keywords.h"
#include "easy_graph/infra/operator.h"

namespace{
	INTERFACE(BaseType) {
		__DECL_COMP(BaseType);
	};

	__DEF_EQUALS(BaseType) {
		return  (typeid(*this) == typeid(rhs));
	}

	__DEF_COMP(BaseType) {
		return (typeid(*this).name() < typeid(rhs).name());
	}

	struct Subtype1 : BaseType {
	};

	struct Subtype2 : BaseType {
	};
}

FIXTURE(TypeCompareTest) {
	Subtype1 s1;
	Subtype1 s2;
	Subtype2 s3;

	const BaseType& b1{s1};
	const BaseType& b2{s2};
	const BaseType& b3{s3};

	TEST("should equal between same class") {
        ASSERT_TRUE(s1 == s2);
    }

	TEST("should equal between same subclasses") {
        ASSERT_TRUE(b1 == b2);
    }

	TEST("should not equal between different class") {
        ASSERT_FALSE(s1 == s3);
    }

	TEST("should not equal between different subclasses") {
        ASSERT_FALSE(b1 == b3);
    }

	TEST("should compare different class") {
        ASSERT_TRUE(s1 < s3);
    }

	TEST("should compare different subclass") {
        ASSERT_TRUE(b1 < b3);
    }
};
