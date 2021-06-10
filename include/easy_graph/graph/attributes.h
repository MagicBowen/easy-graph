#ifndef HE75387E4_E817_4B3C_8228_B2E5178F8BDD
#define HE75387E4_E817_4B3C_8228_B2E5178F8BDD

#include "easy_graph/graph/attribute.h"
#include <map>

EG_NS_BEGIN

struct AttributeVisitor;

struct Attributes {
	Attributes();
	Attributes(std::initializer_list<Attribute>);

	void set(const Attribute&);
	void set(const AttrKey&, const std::any&);

	const std::any* get(const AttrKey&) const;

	template<typename VALUE>
	const VALUE* get(const AttrKey& key) const {
		return std::any_cast<VALUE>(this->get(key));
	}

	void remove(const AttrKey&);

	void merge(const Attributes&);

	void accept(AttributeVisitor&) const;

private:
	std::map<AttrKey, std::any> dict;
};

EG_NS_END

#endif
