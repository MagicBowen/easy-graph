#ifndef H92B288AE_D7F8_4EEB_B0D8_526760F09507
#define H92B288AE_D7F8_4EEB_B0D8_526760F09507

#include "easy_graph/modifier/revise.h"
#include "easy_graph/graph/node.h"

EG_NS_BEGIN

struct NodeAdder : Revise  {

	explicit NodeAdder(Node);

private:
	Status execute(Graph&) const override;

private:
	Node node;
};

EG_NS_END

#endif
