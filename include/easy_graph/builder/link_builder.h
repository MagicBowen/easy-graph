#ifndef HB6C3D460_A84E_4057_9F7F_21C088FD7A27
#define HB6C3D460_A84E_4057_9F7F_21C088FD7A27

#include "easy_graph/builder/link.h"
#include <type_traits>

EG_NS_BEGIN

namespace detail {
	static inline void make_link(Link&) {
	}

	template<typename T, typename ...TS>
	void make_link(Link& link, T && t, TS && ...ts) {
		if constexpr (std::is_base_of_v<EdgeType, std::decay_t<T>>) {
			link.type = &t;
		} else if constexpr (std::is_same_v<PortPair, std::decay_t<T>>) {
			link.setPorts(std::forward<T>(t));
		} else if constexpr (std::is_convertible_v<std::decay_t<T>, PortId>) {
			link.setPort(std::forward<T>(t));
		} else if constexpr (std::is_same_v<Attribute, std::decay_t<T>>) {
			link.attrs.set(std::forward<T>(t));
		} else if constexpr (std::is_same_v<Attributes, std::decay_t<T>>) {
			link.attrs.replace(std::forward<T>(t));
		} else {
			static_assert(!sizeof(T), "Unsupported edge construction type!");
		}
		make_link(link, std::forward<TS>(ts)...);
	}
}

template<typename ...TS>
Link link_of(const EdgeType& type, TS && ...ts) {
	Link link(type);
	detail::make_link(link, std::forward<TS>(ts)...);
	return link;
}

EG_NS_END

#endif
