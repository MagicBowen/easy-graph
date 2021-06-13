#ifndef HA663CE50_65F5_4399_BAF0_AF9569FBBBF6
#define HA663CE50_65F5_4399_BAF0_AF9569FBBBF6

#include "easy_graph/attribute/attributes.h"

EG_NS_BEGIN

struct AttributesMixin {

	void setAttr(const Attribute& attr) {
		attributes.set(attr);
	}

	void setAttr(const AttrKey& key, const std::any& value) {
		attributes.set(key, value);
	}

	const std::any* getAny(const AttrKey& key) const {
		return attributes.get(key);
	}

	template<typename VALUE>
	const VALUE* getAttr(const AttrKey& key) const {
		return attributes.get<VALUE>(key);
	}

	void removeAttr(const AttrKey& key) {
		attributes.remove(key);
	}

	void mergeAttrs(const Attributes& attrs) {
		attributes.merge(attrs);
	}

	void accept(AttributeVisitor& visitor) const {
		attributes.accept(visitor);
	}

private:
	Attributes attributes;
};

EG_NS_END

#endif
