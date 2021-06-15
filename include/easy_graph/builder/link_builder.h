#ifndef HB6C3D460_A84E_4057_9F7F_21C088FD7A27
#define HB6C3D460_A84E_4057_9F7F_21C088FD7A27

#include "easy_graph/builder/link.h"
#include <type_traits>

EG_NS_BEGIN

template<typename ...TS>
Link make_link(const EdgeType& type, TS && ...ts) {
	Link link(type);
	if constexpr (sizeof...(ts) > 0) {
		make_link_impl(link, std::forward<TS>(ts)...);
	}
	return link;
}

template<typename T, typename ...TS>
void make_link_impl(Link& link, T && t, TS && ...ts) {
	if constexpr (std::is_convertible_v<std::decay_t<T>, EdgeType>) {
		link.type = &t;
	} else if constexpr (std::is_same_v<PortPair, std::decay_t<T>>) {
		link.setPorts(std::forward<T>(t));
	} else if constexpr (std::is_convertible_v<std::decay_t<T>, PortId>) {
		link.setPort(std::forward<T>(t));
	} else if constexpr (std::is_same_v<Attribute, std::decay_t<T>>) {
		link.attrs.set(std::forward<T>(t));
	} else if constexpr (std::is_same_v<Attributes, std::decay_t<T>>) {
		link.attrs.merge(std::forward<T>(t));
	} else {
		static_assert(!sizeof(T), "Unsupported edge construction type!");
	}
	if constexpr (sizeof...(ts) > 0) {
		make_link_impl(link, std::forward<TS>(ts)...);
	}
}

#define LINK_OF(...)		::EG_NS::make_link(__VA_ARGS__)

EG_NS_END

#endif
