#include "easy_graph/attribute/attributes.h"
#include "easy_graph/attribute/attribute_visitor.h"

EG_NS_BEGIN

Attributes::Attributes() {
}

Attributes::Attributes(std::initializer_list<Attribute> attrs) {
	for (auto& attr : attrs) {
		dict.insert(std::move(attr));
	}
}
void Attributes::set(Attribute attr) {
	this->set(attr.first, std::move(attr.second));
}

const std::any* Attributes::get(const AttrKey& key) const{
	auto it = dict.find(key);
	if (it == dict.end()) {
		return nullptr;
	}
	return &(it->second);
}

void Attributes::merge(const Attributes& attrs) {
	for (const auto& attr : attrs.dict) {
		this->set(attr.first, attr.second);
	}
}

void Attributes::replace(Attributes attrs) {
	dict = std::move(attrs.dict);
}

void Attributes::remove(const AttrKey& key) {
	dict.erase(key);
}

void Attributes::clear() {
	dict.clear();
}

void Attributes::accept(AttributeVisitor& visitor) const {
	std::for_each(dict.cbegin(), dict.cend(),  [&visitor](const auto& attr){visitor.visit(attr);});
}

EG_NS_END
