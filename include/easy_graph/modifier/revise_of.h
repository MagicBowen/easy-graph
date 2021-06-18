#ifndef HB4194AB6_7AD8_4B17_A271_494A83838933
#define HB4194AB6_7AD8_4B17_A271_494A83838933

#include "easy_graph/builder/node_builder.h"
#include "easy_graph/builder/edge_builder.h"
#include "easy_graph/modifier/revises/node_adder.h"
#include "easy_graph/modifier/revises/node_eraser.h"
#include "easy_graph/modifier/revises/edge_adder.h"
#include "easy_graph/modifier/revises/edge_eraser.h"

EG_NS_BEGIN

/////////////////////////////////////////////////////////////
#define ALIAS_REVISE_OF(REVISE_OF, REVISE, BUILDER)				\
template<typename ...ARGS>										\
RevisePtr REVISE_OF(ARGS && ...args) {							\
	return revise_of<REVISE>(BUILDER(std::forward<ARGS>(args)...));	\
}

/////////////////////////////////////////////////////////////
ALIAS_REVISE_OF(add_node_of, NodeAdder, node_of)
ALIAS_REVISE_OF(erase_node_of, NodeEraser, node_of)
ALIAS_REVISE_OF(add_edge_of, EdgeAdder, edge_of)
ALIAS_REVISE_OF(erase_edge_of, EdgeEraser, edge_of)

EG_NS_END

#endif
