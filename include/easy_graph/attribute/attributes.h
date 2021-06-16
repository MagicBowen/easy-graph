#ifndef HE75387E4_E817_4B3C_8228_B2E5178F8BDD
#define HE75387E4_E817_4B3C_8228_B2E5178F8BDD

#include "easy_graph/attribute/attribute.h"
#include <map>

EG_NS_BEGIN

struct AttributeVisitor;

struct Attributes {
	Attributes();
	Attributes(std::initializer_list<Attribute>);

	template<typename VALUE>
	void set(const AttrKey& key, VALUE&& any) {
		dict.insert_or_assign(key, std::forward<VALUE>(any));
	}

	template<typename VALUE>
	const VALUE* get(const AttrKey& key) const {
		return std::any_cast<VALUE>(this->get(key));
	}

	void set(Attribute);
	const std::any* get(const AttrKey&) const;
	void replace(Attributes);
	void merge(const Attributes&);
	void remove(const AttrKey&);
	void clear();

	void accept(AttributeVisitor&) const;

private:
	std::map<AttrKey, std::any> dict;
};

EG_NS_END

#endif
