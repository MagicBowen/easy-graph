#ifndef HE04F56DE_D19F_49AA_AB12_B892970271AD
#define HE04F56DE_D19F_49AA_AB12_B892970271AD

#include "easy_graph/eg.h"
#include <type_traits>

EG_NS_BEGIN

template<typename E>
constexpr auto enum_underlying_cast(E e) noexcept {
	return static_cast<std::underlying_type_t<E>>(e);
}

EG_NS_END

#endif
