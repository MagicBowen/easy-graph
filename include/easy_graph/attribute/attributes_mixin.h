#ifndef HA663CE50_65F5_4399_BAF0_AF9569FBBBF6
#define HA663CE50_65F5_4399_BAF0_AF9569FBBBF6

#include "easy_graph/attribute/attributes.h"

EG_NS_BEGIN

struct AttributesMixin {

	template<typename ATTR>
	void setAttr(ATTR && attr) {
		attributes.set(std::forward<ATTR>(attr));
	}

	template<typename VALUE>
	void setAttr(const AttrKey& key, VALUE && value) {
		attributes.set(key, std::forward<VALUE>(value));
	}

	const std::any* getAny(const AttrKey& key) const {
		return attributes.get(key);
	}

	template<typename VALUE>
	const VALUE* getAttr(const AttrKey& key) const {
		return attributes.get<VALUE>(key);
	}

	template<typename ATTRS>
	void replaceAttrs(ATTRS && attrs) {
		attributes.replace(std::forward<ATTRS>(attrs));
	}

	void mergeAttrs(const Attributes& attrs) {
		attributes.merge(attrs);
	}

	void removeAttr(const AttrKey& key) {
		attributes.remove(key);
	}

	void accept(AttributeVisitor& visitor) const {
		attributes.accept(visitor);
	}

private:
	Attributes attributes;
};

EG_NS_END

#endif
