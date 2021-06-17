#ifndef HA103E26C_274E_47F6_9A12_1A21ED8D1357
#define HA103E26C_274E_47F6_9A12_1A21ED8D1357

#include "easy_graph/graph/edge.h"

EG_NS_BEGIN

enum class Status;
struct Graph;

struct EdgeAdder {
	EdgeAdder(const Edge&);

	Status execute(Graph&) const;

private:
	Edge edge;
};
EG_NS_END

#endif
