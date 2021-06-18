#ifndef HE5572875_5B0D_4A0C_AECF_B0522480BC5D
#define HE5572875_5B0D_4A0C_AECF_B0522480BC5D

#include "easy_graph/modifier/revises/node_adder.h"
#include "easy_graph/modifier/revises/node_eraser.h"
#include "easy_graph/modifier/revises/edge_adder.h"
#include "easy_graph/modifier/revises/edge_eraser.h"
#include "easy_graph/modifier/revise_of.h"
#include <variant>

EG_NS_BEGIN

using Revise = std::variant<NodeAdder, NodeEraser, EdgeAdder, EdgeEraser, ReviseOf>;

EG_NS_END

#endif
