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
	TEST("uninitialized any has no value") {
		std::any any ;
		ASSERT_FALSE(any.has_value());
	}

	TEST("initialized any has correct value type") {
		std::any any = LabelType("test");
		ASSERT_TRUE(any.has_value());
		ASSERT_TRUE(typeid(LabelType) == any.type());
	}

	TEST("should cast any to value in it") {
		std::any any = LabelType("test");
		Base* lt = std::any_cast<LabelType>(&any);
		ASSERT_TRUE(lt);
		ASSERT_EQ(std::string("test"), lt->getType());
	}

	TEST("should not cast any to the supper class value of which in it") {
		std::any any = LabelType("test");
		Base* lb = std::any_cast<Base>(&any);
		ASSERT_FALSE(lb);
	}
};
