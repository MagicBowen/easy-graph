#ifndef H1862D663_769E_4D7D_B59A_23D7350EB7C0
#define H1862D663_769E_4D7D_B59A_23D7350EB7C0

#include "easy_graph/infra/singleton.h"

EG_NS_BEGIN

struct EdgeType;

SINGLETON(DefaultEdgeType) {
	void reg(const EdgeType&);
	const EdgeType& get() const;
	void reset();

private:
	const EdgeType* type{nullptr};
};

#define EDGE_DEFAULT   ::EG_NS::DefaultEdgeType::getInstance().get()

EG_NS_END

#endif
