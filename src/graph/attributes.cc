#include "easy_graph/graph/attributes.h"

EG_NS_BEGIN

Attributes::Attributes() {
}

Attributes::Attributes(std::initializer_list<Attribute> attrs) {
	for (auto& attr : attrs) {
		dict.insert(attr);
	}
}

std::any* Attributes::get(const AttrKey& key) {
	auto it = dict.find(key);
	if (it == dict.end()) {
		return nullptr;
	}
	return &(it->second);
}

void Attributes::set(const AttrKey& key, const std::any& any) {
	dict.insert_or_assign(key, any);
}

void Attributes::remove(const AttrKey& key) {
	dict.erase(key);
}

EG_NS_END
