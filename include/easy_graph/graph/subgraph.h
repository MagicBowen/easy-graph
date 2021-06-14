#ifndef H4061B54F_E374_409C_85DB_AFD8F1E80AF0
#define H4061B54F_E374_409C_85DB_AFD8F1E80AF0

#include "easy_graph/infra/operator.h"
#include "easy_graph/graph/wire.h"
#include <vector>
#include <string>

EG_NS_BEGIN

struct Graph;
struct WireVisitor;

struct Subgraph {
	Subgraph(const Graph&);
	Subgraph(const std::string& name, const Graph&);

	__DECL_EQUALS(Subgraph);

	void setName(const std::string&);
	std::string getName() const;

	const Graph& getGraph() const;

	void wireUp(const InputWire&);
	void wireUp(const OutputWire&);

	void accept(WireVisitor&) const;

private:
	std::string name;
	const Graph& graph;
	std::vector<Wire> inputWires;
	std::vector<Wire> outputWires;
};

EG_NS_END

#endif
