#ifndef H550E4ACB_BEC7_4E71_8C6F_CD7FA53662A9
#define H550E4ACB_BEC7_4E71_8C6F_CD7FA53662A9

#include "easy_graph/status.h"
#include "flow_direction.h"

EG_NS_BEGIN

struct Graph;

struct GraphLayout {
	static Status layout(const Graph& graph, FlowDirection direction);
};

EG_NS_END

#endif
