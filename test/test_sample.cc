#include <cctest/cctest.h>

FIXTURE(SampleTest) {
	BEFORE {
	}

	AFTER{
	}

	TEST("should fail") {
		ASSERT_TRUE(false);
	}
};
