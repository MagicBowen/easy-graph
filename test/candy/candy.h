#ifndef H4CA9DC4C_77FC_440E_B527_F1D807793342
#define H4CA9DC4C_77FC_440E_B527_F1D807793342

#include "easy_graph/infra/keywords.h"
#include <string>

EG_NS_BEGIN

INTERFACE(Candy) {
	ABSTRACT(std::string getLabel() const);
};

EG_NS_END

#endif
