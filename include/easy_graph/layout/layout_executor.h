#ifndef HE4984335_C586_4533_A056_27F9F996DF50
#define HE4984335_C586_4533_A056_27F9F996DF50

#include "easy_graph/infra/status.h"
#include "easy_graph/infra/keywords.h"

EG_NS_BEGIN

struct Graph;
struct LayoutOption;

INTERFACE(layoutExecutor) {
	ABSTRACT(Status layout(const Graph&, const LayoutOption*));
};

EG_NS_END

#endif
