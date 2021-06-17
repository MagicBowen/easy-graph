#ifndef H715F10A2_C604_4484_9570_1BC07809175D
#define H715F10A2_C604_4484_9570_1BC07809175D

#include "easy_graph/graph/node_id.h"

EG_NS_BEGIN

enum class Status;
struct Graph;

struct NodeEraser {
	NodeEraser(const NodeId&);

	Status execute(Graph&) const;

private:
	NodeId id;
};

EG_NS_END

#endif
