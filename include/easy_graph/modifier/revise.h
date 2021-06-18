#ifndef HE5572875_5B0D_4A0C_AECF_B0522480BC5D
#define HE5572875_5B0D_4A0C_AECF_B0522480BC5D

#include "easy_graph/infra/keywords.h"
#include <memory>

EG_NS_BEGIN

enum class Status;
struct Graph;

/////////////////////////////////////////////////////////////
INTERFACE(Revise) {
	ABSTRACT(Status execute(Graph&) const);
};

/////////////////////////////////////////////////////////////
using RevisePtr = std::unique_ptr<Revise>;

/////////////////////////////////////////////////////////////
template<typename REVISE, typename ...ARGS>
RevisePtr revise_of(ARGS && ...args) {
	return std::make_unique<REVISE>(std::forward<ARGS>(args)...);
}

EG_NS_END

#endif
