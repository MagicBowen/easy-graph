#ifndef H02FEE2D5_7CD9_43BC_B74D_590BD6A7C8A9
#define H02FEE2D5_7CD9_43BC_B74D_590BD6A7C8A9

#include "easy_graph/modifier/graph_modifier.h"

EG_NS_BEGIN

enum class Status;

template<typename ...RS>
Status modifier_exec(Graph& graph, RS && ...rs) {
	GraphModifier modifier(graph);
	(modifier.addRevise(std::forward<RS>(rs)), ...);
	return modifier.commit();
}

EG_NS_END

#endif
