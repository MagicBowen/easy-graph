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

	template<typename ANYTHING>
	using BoxedAnything = std::conditional_t<std::is_base_of_v<Box, ANYTHING>, ANYTHING, BoxWrapper<ANYTHING>>;
}

#define BOX_WRAPPER(ANYTHING)  ::EG_NS::detail::BoxedAnything<ANYTHING>
#define BOX_OF(ANYTHING, ...)  ::EG_NS::box_packing<BOX_WRAPPER(ANYTHING)>(__VA_ARGS__)

EG_NS_END

#endif
