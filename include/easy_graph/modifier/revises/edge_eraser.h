#ifndef H14B7CCCE_B926_4673_BD3B_36F242FC5C59
#define H14B7CCCE_B926_4673_BD3B_36F242FC5C59

#include "easy_graph/modifier/revise.h"
#include "easy_graph/graph/edge.h"

EG_NS_BEGIN

struct EdgeEraser : Revise {

	explicit EdgeEraser(const Edge&);

private:
	Status execute(Graph&) const override;

private:
	Edge edge;
};

EG_NS_END

#endif
