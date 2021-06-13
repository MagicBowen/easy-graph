#include "easy_graph/graph/edge_type_repo.h"

EG_NS_BEGIN

void EdgeTypeRepo::registerType(EdgeTypeIndex index, const EdgeType& type) {
	edgeTypes[index] = &type;
}

const EdgeType* EdgeTypeRepo::getType(EdgeTypeIndex index) const {
	auto it = edgeTypes.find(index);
	if (it == edgeTypes.end()) {
		return nullptr;
	}
	return it->second;
}

EG_NS_END
