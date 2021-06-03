#ifndef HE7D53295_59F0_46B0_A881_D6A33B1F9C14
#define HE7D53295_59F0_46B0_A881_D6A33B1F9C14

#include "easy_graph/graph/box.h"
#include <type_traits>

EG_NS_BEGIN

namespace detail {
	template<typename Anything>
	struct BoxWrapper : Anything, Box {
		using Anything::Anything;
	};

	template<typename Anything>
	using BoxedAnything = std::conditional_t<std::is_base_of_v<Box, Anything>, Anything, BoxWrapper<Anything>>;
}

#define BOX_WRAPPER(Anything)  ::EG_NS::detail::BoxedAnything<Anything>
#define BOX_OF(Anything, ...)  ::EG_NS::box_packing<BOX_WRAPPER(Anything)>(__VA_ARGS__)

EG_NS_END

#endif
