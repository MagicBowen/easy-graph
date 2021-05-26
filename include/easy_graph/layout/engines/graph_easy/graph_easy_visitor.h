#ifndef HB6783151_C24E_4DA3_B969_46C2298FF43F
#define HB6783151_C24E_4DA3_B969_46C2298FF43F

#include "easy_graph/graph/graph_visitor.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_layout_context.h"
#include <string>

EG_NS_BEGIN

struct GraphEasyOption;

struct GraphEasyVisitor : GraphVisitor {
	GraphEasyVisitor(const GraphEasyOption&);

	std::string getLayout() const;

private:
	Status visit(const Graph&) override;
	Status visit(const Node&) override;
	Status visit(const Edge&) override;

private:
	std::string layout;
	GraphEasyLayoutContext ctxt;
};

EG_NS_END

#endif
