#include "easy_graph/modifier/revises/any_revise.h"

EG_NS_BEGIN

Status AnyRevise::execute(Graph& graph) const {
	return revise(graph);
}

EG_NS_END
