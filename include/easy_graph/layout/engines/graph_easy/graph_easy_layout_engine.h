#ifndef HAC96EB3A_2169_4BB0_A8EB_7B966C262B2F
#define HAC96EB3A_2169_4BB0_A8EB_7B966C262B2F

#include "easy_graph/layout/layout_engine.h"

EG_NS_BEGIN

struct GraphEasyLayoutEngine : LayoutEngine {
private:
	Status layout(const Graph&, const LayoutOption*) override;
};

EG_NS_END

#endif
