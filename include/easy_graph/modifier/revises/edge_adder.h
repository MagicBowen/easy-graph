#ifndef HA103E26C_274E_47F6_9A12_1A21ED8D1357
#define HA103E26C_274E_47F6_9A12_1A21ED8D1357

#include "easy_graph/modifier/revise.h"
#include "easy_graph/graph/edge.h"

EG_NS_BEGIN

struct EdgeAdder : Revise {

	explicit EdgeAdder(const Edge&);

private:
	Status execute(Graph&) const override;

private:
	Edge edge;
};

EG_NS_END

#endif
