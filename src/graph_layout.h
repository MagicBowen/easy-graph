#ifndef H550E4ACB_BEC7_4E71_8C6F_CD7FA53662A9
#define H550E4ACB_BEC7_4E71_8C6F_CD7FA53662A9

#include "easy_graph/status.h"

EG_NS_BEGIN

struct LayoutOption;
struct Graph;

struct GraphLayout {
	static void config(const LayoutOption&);
	static Status layout(const Graph& , const LayoutOption*);
};

EG_NS_END

#endif
