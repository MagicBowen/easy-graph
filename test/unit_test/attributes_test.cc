#include <cctest/cctest.h>
#include "easy_graph/attribute/attributes.h"

USING_EG_NS

FIXTURE(AttributesTest) {

	TEST("should get attribute") {
		Attributes attrDict{{"name", std::string("Bowen")}};

		auto name = attrDict.get("name");
        ASSERT_TRUE(name);

        ASSERT_FALSE(attrDict.get<int>("name"));

        auto namePtr = attrDict.get<std::string>("name");
        ASSERT_EQ(std::string("Bowen"), *namePtr);
    }

	TEST("should get attribute by specified correct type") {
		Attributes attrDict{{"age", 30}};

        auto age = attrDict.get<int>("age");
        ASSERT_TRUE(age);
        ASSERT_EQ(30, *age);
	}

	TEST("should get null attribute by wrong type") {
		Attributes attrDict{{"height", 178.5}};

        auto weight = attrDict.get<int>("weight");
        ASSERT_FALSE(weight);
	}

	TEST("should set none existed attribute success") {
		Attributes attrDict;
		attrDict.set("name", std::string("Jerry"));

        auto name = attrDict.get<std::string>("name");
        ASSERT_TRUE(name);
        ASSERT_EQ(std::string("Jerry"), *name);
	}

	TEST("should set existed attribute success") {
		Attributes attrDict{{"name", std::string("Bowen")}};
		attrDict.set("name", std::string("Jerry"));

        auto name = attrDict.get<std::string>("name");
        ASSERT_TRUE(name);
        ASSERT_EQ(std::string("Jerry"), *name);
	}
};
