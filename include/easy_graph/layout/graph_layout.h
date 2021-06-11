#ifndef H550E4ACB_BEC7_4E71_8C6F_CD7FA53662A9
#define H550E4ACB_BEC7_4E71_8C6F_CD7FA53662A9

#include "easy_graph/infra/status.h"
#include "easy_graph/infra/singleton.h"

EG_NS_BEGIN

struct LayoutEngine;
struct LayoutOption;
struct Graph;

SINGLETON(GraphLayout) {
	void config(LayoutEngine&, const LayoutOption* = nullptr);
	Status layout(const Graph&, const LayoutOption* = nullptr);

private:
	LayoutEngine* executor{nullptr};
	const LayoutOption* options{nullptr};
};

EG_NS_END

#endif
