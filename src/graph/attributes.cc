#include "easy_graph/graph/attributes.h"
#include "easy_graph/graph/attribute_visitor.h"

EG_NS_BEGIN

Attributes::Attributes() {
}

Attributes::Attributes(std::initializer_list<Attribute> attrs) {
	for (auto& attr : attrs) {
		dict.insert(attr);
	}
}

const std::any* Attributes::get(const AttrKey& key) const{
	auto it = dict.find(key);
	if (it == dict.end()) {
		return nullptr;
	}
	return &(it->second);
}

void Attributes::set(const Attribute& attr) {
	this->set(attr.first, attr.second);
}

void Attributes::set(const AttrKey& key, const std::any& any) {
	dict.insert_or_assign(key, any);
}

void Attributes::merge(const Attributes& attrs) {
	for (auto& attr : attrs.dict) {
		this->set(attr.first, attr.second);
	}
}

void Attributes::remove(const AttrKey& key) {
	dict.erase(key);
}

void Attributes::clear() {
	dict.clear();
}

void Attributes::accept(AttributeVisitor& visitor) const {
	std::for_each(dict.begin(), dict.end(),  [&visitor](const auto& attr){visitor.visit(attr);});
}

EG_NS_END
