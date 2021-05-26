#ifndef H13960AED_B5B1_45F9_A664_6CB6C15CA3C1
#define H13960AED_B5B1_45F9_A664_6CB6C15CA3C1

#include "easy_graph/infra/keywords.h"
#include "easy_graph/infra/status.h"

EG_NS_BEGIN

struct Graph;
struct Node;
struct Edge;

INTERFACE(GraphVisitor) {
	DEFAULT(Status, visit(const Graph&));
	DEFAULT(Status, visit(const Node&));
	DEFAULT(Status, visit(const Edge&));
};

EG_NS_END

#endif
