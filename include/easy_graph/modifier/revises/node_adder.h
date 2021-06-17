#ifndef H92B288AE_D7F8_4EEB_B0D8_526760F09507
#define H92B288AE_D7F8_4EEB_B0D8_526760F09507

#include "easy_graph/graph/node.h"

EG_NS_BEGIN

enum class Status;
struct Graph;

struct NodeAdder {
	NodeAdder(Node);

	Status execute(Graph&) const;

private:
	Node node;
};

EG_NS_END

#endif
