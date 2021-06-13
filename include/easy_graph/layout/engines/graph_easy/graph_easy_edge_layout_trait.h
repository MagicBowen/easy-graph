#ifndef H5978DF09_31C2_4FAD_9CCF_045609B2F7B3
#define H5978DF09_31C2_4FAD_9CCF_045609B2F7B3

#include "easy_graph/infra/keywords.h"
#include <string>

EG_NS_BEGIN

INTERFACE(GraphEasyEdgeLayoutTrait) {
	ABSTRACT(std::string getArrow() const);
};

EG_NS_END

#endif
