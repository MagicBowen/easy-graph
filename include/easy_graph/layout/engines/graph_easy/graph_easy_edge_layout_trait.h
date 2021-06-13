#ifndef H5978DF09_31C2_4FAD_9CCF_045609B2F7B3
#define H5978DF09_31C2_4FAD_9CCF_045609B2F7B3

#include "easy_graph/infra/keywords.h"
#include <string>

EG_NS_BEGIN

struct Edge;
struct GraphEasyLayoutContext;

INTERFACE(GraphEasyEdgeLayoutTrait) {
	ABSTRACT(std::string getAttrLayout(const Edge&, GraphEasyLayoutContext&) const);
	ABSTRACT(std::string getArrowLayout(const Edge&, GraphEasyLayoutContext&) const);
};

EG_NS_END

#endif
