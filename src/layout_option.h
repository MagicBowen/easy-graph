#ifndef H37156CC2_92BD_44DA_8DA7_A11629E762BE
#define H37156CC2_92BD_44DA_8DA7_A11629E762BE

#include "easy_graph/eg.h"

EG_NS_BEGIN

enum class FlowDir {
	LR = 0,
	TB,
};

enum class LayoutType {
	FREE = 0,
	REGULAR,
};

struct LayoutOption {
	static const LayoutOption& getDefault() {
		static LayoutOption option;
		return option;
	}

	FlowDir dir{FlowDir::LR};
	LayoutType type{LayoutType::FREE};
	size_t scale{1};
};

EG_NS_END

#endif
