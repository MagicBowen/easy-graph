#ifndef H2D62ED79_6780_4C04_8665_E3B0D1B951E6
#define H2D62ED79_6780_4C04_8665_E3B0D1B951E6

#include "easy_graph/eg.h"

EG_NS_BEGIN

template<typename Trait, typename Object>
const Trait* trait_cast(const Object& object) {
	return dynamic_cast<const Trait*>(&object);
}

template<typename Trait, typename Object>
Trait* trait_cast(Object& object) {
	return dynamic_cast<Trait*>(&object);
}

EG_NS_END

#endif
