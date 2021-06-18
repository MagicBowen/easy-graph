#ifndef H02FEE2D5_7CD9_43BC_B74D_590BD6A7C8A9
#define H02FEE2D5_7CD9_43BC_B74D_590BD6A7C8A9

#include "easy_graph/modifier/graph_modifier.h"
#include "easy_graph/modifier/revises/any_revise.h"
#include <type_traits>

EG_NS_BEGIN

enum class Status;

namespace {
	static inline void make_graph_modifier(GraphModifier& modifier) {
	}

	template<typename R, typename ...RS>
	void make_graph_modifier(GraphModifier& modifier, R && r,  RS && ...rs) {
		if constexpr (std::is_same_v<RevisePtr, std::decay_t<R>>) {
			modifier.addRevise(std::forward<R>(r));
		} else if constexpr (std::is_invocable_v<R, Graph&>) {
			modifier.addRevise(revise_of<AnyRevise>(std::forward<R>(r)));
		} else {
			static_assert(!sizeof(R), "Unsupported modifier construction type!");
		}
		make_graph_modifier(modifier, std::forward<RS>(rs)...);
	};
}

template<typename ...RS>
Status graph_modify_execute(Graph& graph, RS && ...rs) {
	GraphModifier modifier(graph);
	make_graph_modifier(modifier, std::forward<RS>(rs)...);
	return modifier.commit();
}

template<typename ...RS>
Status graph_modify_atom_execute(Graph& graph, RS && ...rs) {
	GraphModifier modifier(graph);
	make_graph_modifier(modifier, std::forward<RS>(rs)...);
	return modifier.commit(true);
}

EG_NS_END

#endif
