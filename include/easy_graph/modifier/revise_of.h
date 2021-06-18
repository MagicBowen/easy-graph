#ifndef HF0845773_1838_4A87_B275_021224783E2E
#define HF0845773_1838_4A87_B275_021224783E2E

#include "easy_graph/eg.h"
#include <functional>

EG_NS_BEGIN

struct Graph;
enum class Status;

struct ReviseOf{
	template<typename REVISE>
	ReviseOf(REVISE && revise)
	: revise(std::forward<REVISE>(revise)) {
	}

	Status execute(Graph& graph) const {
		return revise(graph);
	}

private:
	std::function<Status (Graph&)> revise;
};

EG_NS_END

#endif
