#ifndef HD6AEBEB1_C426_411D_9859_EB81838E49D0
#define HD6AEBEB1_C426_411D_9859_EB81838E49D0

#include <cctest/cctest.h>
#include "easy_graph/infra/keywords.h"
#include <any>

USING_EG_NS

namespace {
	INTERFACE(Base) {
		ABSTRACT(std::string getType() const);
	};

	struct LabelType : Base {
		LabelType(const std::string& label)
		: label(label) {
		}

	private:
		std::string getType() const override {
			return label;
		}
	private:
		std::string label;
	};
}

FIXTURE(AnyTest) {
	TEST("basic features") {
		std::any any ;
		ASSERT_FALSE(any.has_value());

		any = LabelType("test");
		ASSERT_TRUE(any.has_value());
		ASSERT_TRUE(typeid(LabelType) == any.type());

		Base* lt = std::any_cast<LabelType>(&any);
		ASSERT_TRUE(lt);
		ASSERT_EQ(std::string("test"), lt->getType());

		Base* lb = std::any_cast<Base>(&any);
		ASSERT_FALSE(lb);
	}
};

#endif
