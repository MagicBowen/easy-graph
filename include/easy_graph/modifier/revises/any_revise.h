#ifndef HF0845773_1838_4A87_B275_021224783E2E
#define HF0845773_1838_4A87_B275_021224783E2E

#include "easy_graph/modifier/revise.h"
#include <functional>

EG_NS_BEGIN

struct AnyRevise : Revise {

	template<typename REVISE>
	explicit AnyRevise(REVISE && revise)
	: revise(std::forward<REVISE>(revise)) {
	}

private:
	Status execute(Graph&) const override;

private:
	std::function<Status (Graph&)> revise;
};

EG_NS_END

#endif
