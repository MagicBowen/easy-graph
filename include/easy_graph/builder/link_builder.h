#ifndef HB6C3D460_A84E_4057_9F7F_21C088FD7A27
#define HB6C3D460_A84E_4057_9F7F_21C088FD7A27

#include "easy_graph/builder/link.h"
#include <type_traits>

EG_NS_BEGIN

template<typename ...TS>
void makeLink(Link& link, TS && ...ts) {
	if constexpr (sizeof...(ts) > 0) {
		makeLinkImpl(link, std::forward<TS>(ts)...);
	}
}

template<typename T, typename ...TS>
void makeLinkImpl(Link& link, T && t, TS && ...ts) {
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
		makeLinkImpl(link, std::forward<TS>(ts)...);
	}
}

EG_NS_END

#endif
