#ifndef H783CD9F9_6FBE_4B58_AA24_ECC8124CD34F
#define H783CD9F9_6FBE_4B58_AA24_ECC8124CD34F

#include "easy_graph/infra/singleton.h"
#include "easy_graph/graph/edge_type_index.h"
#include <map>

EG_NS_BEGIN

struct EdgeType;

SINGLETON(EdgeTypeRepo) {
	void registerType(EdgeTypeIndex, const EdgeType&);
	const EdgeType* getType(EdgeTypeIndex) const;

private:
	std::map<EdgeTypeIndex, const EdgeType*> edgeTypes;
};

EG_NS_END

#endif
