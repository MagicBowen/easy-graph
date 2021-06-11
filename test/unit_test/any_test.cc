#include <cctest/cctest.h>
#include "easy_graph/infra/keywords.h"
#include <any>

#include <iostream>

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
	TEST("uninitialized any with no value") {
		std::any any ;
		ASSERT_FALSE(any.has_value());
	}

	TEST("initialized any with correct value type") {
		std::any any = LabelType("test");
		ASSERT_TRUE(any.has_value());
		ASSERT_TRUE(typeid(LabelType) == any.type());
	}

	TEST("should cast any to value type in it") {
		std::any any = LabelType("test");
		Base* lt = std::any_cast<LabelType>(&any);
		ASSERT_TRUE(lt);
		ASSERT_EQ(std::string("test"), lt->getType());
	}

	TEST("should not cast any to the supper class value") {
		std::any any = LabelType("test");
		Base* lb = std::any_cast<Base>(&any);
		ASSERT_FALSE(lb);
	}

	TEST("should not cast any to the convertible type") {
		std::any any("hello");
		auto value = std::any_cast<std::string>(&any);
		ASSERT_FALSE(value);
	}

	TEST("should cast any to the specified make type") {
		std::any any = std::make_any<std::string>("hello");
		auto value = std::any_cast<std::string>(&any);
		ASSERT_TRUE(value);
		ASSERT_EQ(std::string("hello"), *value);
	}
};
