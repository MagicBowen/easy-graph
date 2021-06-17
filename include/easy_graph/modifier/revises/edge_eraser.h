#ifndef H14B7CCCE_B926_4673_BD3B_36F242FC5C59
#define H14B7CCCE_B926_4673_BD3B_36F242FC5C59

#include "easy_graph/eg.h"
#include "easy_graph/graph/edge.h"

EG_NS_BEGIN

enum class Status;
struct Graph;

struct EdgeEraser {
	EdgeEraser(const Edge&);

	Status execute(Graph&) const;

private:
	Edge edge;
};


EG_NS_END

#endif
