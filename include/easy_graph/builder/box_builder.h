#ifndef H685B8672_04C0_4AD6_91BB_EB9F1A372154
#define H685B8672_04C0_4AD6_91BB_EB9F1A372154

#include "easy_graph/graph/box.h"
#include <type_traits>

EG_NS_BEGIN

template<typename RET, typename CONTENT>
struct BoxBuilder : CONTENT, Box {
	typedef RET (CONTENT::*ID_FUNC)() const;
	template<typename... Args>
	BoxBuilder(ID_FUNC idFunc, Args&&... args)
	: CONTENT(args...) , func(idFunc) {
	}

private:
	NodeId getId() const override {
		using RESULT_TYPE = typename std::decay<RET>::type;
		if constexpr (std::is_convertible<RESULT_TYPE, NodeId>::value) {
			return (this->*(func))();
		} else {
			return std::to_string((this->*(func))());
		}
	}
	ID_FUNC func;
};

EG_NS_END

#endif
