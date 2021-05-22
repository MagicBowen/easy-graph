#ifndef H550E4ACB_BEC7_4E71_8C6F_CD7FA53662A9
#define H550E4ACB_BEC7_4E71_8C6F_CD7FA53662A9

#include "easy_graph/eg.h"
#include "easy_graph/status.h"

EG_NS_BEGIN

struct Graph;

struct GraphLayout {
	GraphLayout(const Graph& graph);
	Status layout() const;

private:
	const Graph& graph;
};

EG_NS_END

#endif
