#ifndef H1B5DAE83_EF97_4254_8F53_C90A787E6D53
#define H1B5DAE83_EF97_4254_8F53_C90A787E6D53

#include "easy_graph/attribute/attributes.h"

EG_NS_BEGIN

template<typename ANY>
Attribute attr_of(const std::string& key, ANY && any) {
	return Attribute(key, std::forward<ANY>(any));
}

static inline Attributes attrs_of(std::initializer_list<Attribute> attrs) {
	Attributes result(std::move(attrs));
	return result;
}

EG_NS_END

#endif
