#ifndef HE7D53295_59F0_46B0_A881_D6A33B1F9C14
#define HE7D53295_59F0_46B0_A881_D6A33B1F9C14

#include "easy_graph/graph/box.h"
#include <type_traits>

EG_NS_BEGIN

namespace detail {
	template<typename ANYTHING>
	struct BoxWrapper : ANYTHING, Box {
		using ANYTHING::ANYTHING;
	};
}

template<typename ANYTHING>
using box_wrapper = std::conditional_t<std::is_base_of_v<Box, ANYTHING>, ANYTHING, detail::BoxWrapper<ANYTHING>>;

template<typename ANYTHING, typename ...ARGS>
BoxPtr box_of(ARGS && ...args) {
	return box_packing<box_wrapper<ANYTHING>>(std::forward<ARGS>(args)...);
}

EG_NS_END

#endif
