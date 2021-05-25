#ifndef H0910832B_890C_4245_B274_55C475EC6DBD
#define H0910832B_890C_4245_B274_55C475EC6DBD

#include "easy_graph/eg.h"
#include "keywords.h"
#include <string>

EG_NS_BEGIN

struct LayoutOption;

INTERFACE(Layoutable) {
	ABSTRACT(std::string getLayout(const LayoutOption&) const);
};

EG_NS_END

#endif
