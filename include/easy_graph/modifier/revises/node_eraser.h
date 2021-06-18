#ifndef H715F10A2_C604_4484_9570_1BC07809175D
#define H715F10A2_C604_4484_9570_1BC07809175D

#include "easy_graph/modifier/revise.h"
#include "easy_graph/graph/node_id.h"

EG_NS_BEGIN

struct Node;

struct NodeEraser : Revise  {

	explicit NodeEraser(const Node&);

private:
	Status execute(Graph&) const override;

private:
	NodeId id;
};

EG_NS_END

#endif
