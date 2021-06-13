#include "easy_graph/graph/subgraph.h"
#include "easy_graph/graph/graph.h"
#include "easy_graph/graph/wire_visitor.h"
#include "easy_graph/infra/vector_eq.h"

EG_NS_BEGIN

namespace {
	bool isWiresEqual(const std::vector<Wire>& lhs, const std::vector<Wire>& rhs) {
		return is_vector_unorder_equal(lhs, rhs);
	}
}

Subgraph::Subgraph(const Graph& graph)
: name(graph.getName()), graph(graph){
}

Subgraph::Subgraph(const std::string& name, const Graph& graph)
: name(name), graph(graph) {
}

__DEF_EQUALS(Subgraph) {
	return (this->graph == rhs.graph) &&
		   isWiresEqual(inputWires, rhs.inputWires) &&
		   isWiresEqual(outputWires, rhs.outputWires);
}

std::string Subgraph::getName() const {
	return name;
}

const Graph& Subgraph::getGraph() const {
	return graph;
}

void Subgraph::wireUpInput(const Wire& wire) {
	inputWires.push_back(wire);
}

void Subgraph::wireUpOutput(const Wire& wire) {
	outputWires.push_back(wire);
}

void Subgraph::accept(WireVisitor& visitor) const {
	std::for_each(inputWires.begin(), inputWires.end(),  [&visitor](const auto& wire){visitor.visitInput(wire);});
	std::for_each(outputWires.begin(), outputWires.end(),  [&visitor](const auto& wire){visitor.visitOutput(wire);});
}

EG_NS_END
