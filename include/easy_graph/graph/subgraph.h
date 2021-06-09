#ifndef H4061B54F_E374_409C_85DB_AFD8F1E80AF0
#define H4061B54F_E374_409C_85DB_AFD8F1E80AF0

#include "easy_graph/eg.h"
#include "easy_graph/infra/operator.h"
#include <string>

EG_NS_BEGIN

struct Graph;

struct Subgraph {
	Subgraph(const Graph&);
	Subgraph(const std::string& name, const Graph&);

	__DECL_EQUALS(Subgraph);

	std::string getName() const;
	const Graph& getGraph() const;

private:
	std::string name;
	const Graph& graph;
};

EG_NS_END

#endif
