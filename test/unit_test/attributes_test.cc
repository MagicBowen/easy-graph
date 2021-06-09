#include <cctest/cctest.h>
#include <string>
#include <any>
#include <map>

namespace {
    using AttrKey = std::string;
	using Attribute = std::pair<AttrKey, std::any>;

	struct Attributes {
		Attributes() {
		}

		Attributes(std::initializer_list<Attribute> attrs) {
			for (auto& attr : attrs) {
				dict.insert(attr);
			}
		}

		std::any* get(const AttrKey& key) {
			auto it = dict.find(key);
			if (it == dict.end()) {
				return nullptr;
			}
			return &(it->second);
		}

		template<typename VALUE>
		VALUE* get(const AttrKey& key) {
			return std::any_cast<VALUE>(this->get(key));
		}

		void set(const AttrKey& key, const std::any& any) {
			dict.insert_or_assign(key, any);
		}

		void remove(const AttrKey& key) {
			dict.erase(key);
		}

	private:
		std::map<AttrKey, std::any> dict;
	};
}

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
