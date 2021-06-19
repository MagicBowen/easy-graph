#ifndef H835D1C92_F2A5_482D_A021_711F0ACC271B
#define H835D1C92_F2A5_482D_A021_711F0ACC271B

#include "easy_graph/graph/graph_visitor.h"
#include "easy_graph/graph/edge.h"

EG_NS_BEGIN

struct EdgeAssertVisitor: GraphVisitor {
	EdgeAssertVisitor(const Edge& edge);

	bool isTypeEqual(const EdgeType&) const;

    template<typename VALUE>
	const VALUE* getAttr(const AttrKey& key) const {
		return edge.getAttr<VALUE>(key);
	}

private:
	const Edge& edge;
};

EG_NS_END

#endif
