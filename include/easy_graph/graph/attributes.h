#ifndef HE75387E4_E817_4B3C_8228_B2E5178F8BDD
#define HE75387E4_E817_4B3C_8228_B2E5178F8BDD

#include "easy_graph/graph/attribute.h"
#include <map>

EG_NS_BEGIN

struct Attributes {
	Attributes();
	Attributes(std::initializer_list<Attribute>);

	std::any* get(const AttrKey&);
	void set(const AttrKey&, const std::any&);
	void remove(const AttrKey&);

	template<typename VALUE>
	VALUE* get(const AttrKey& key) {
		return std::any_cast<VALUE>(this->get(key));
	}

private:
	std::map<AttrKey, std::any> dict;
};

EG_NS_END

#endif
