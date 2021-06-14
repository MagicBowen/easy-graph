#ifndef H079D3C0C_1D82_403B_91DE_E449C4893172
#define H079D3C0C_1D82_403B_91DE_E449C4893172

#include "easy_graph/eg.h"
#include <vector>

EG_NS_BEGIN

template<typename T>
bool is_vector_unorder_equal(const std::vector<T>& lhs, const std::vector<T>& rhs) {
	if (lhs.size() != rhs.size()) return false;
	for (auto item : lhs) {
		auto result = std::find_if(rhs.cbegin(), rhs.cend(), [&item](const auto& other) {
			return item == other;
		});
		if (result == rhs.end()) return false;
	}
	return true;
}

EG_NS_END

#endif
