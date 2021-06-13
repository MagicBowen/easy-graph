#ifndef H2D62ED79_6780_4C04_8665_E3B0D1B951E6
#define H2D62ED79_6780_4C04_8665_E3B0D1B951E6

#include "easy_graph/eg.h"

EG_NS_BEGIN

template<typename TRAIT, typename OBJECT>
const TRAIT* trait_cast(const OBJECT& object) {
	return dynamic_cast<const TRAIT*>(&object);
}

template<typename TRAIT, typename OBJECT>
TRAIT* trait_cast(OBJECT& object) {
	return dynamic_cast<TRAIT*>(&object);
}

EG_NS_END

#endif
