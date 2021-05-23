#ifndef H4796C8F5_EA30_46B8_9308_5F0D8BF02CCE
#define H4796C8F5_EA30_46B8_9308_5F0D8BF02CCE

#include "edge_type.h"
#include <string>

EG_NS_BEGIN

struct EdgeId {
	EdgeType type;
	std::string srcName;
	std::string dstName;
	size_t srcPortIndex;
	size_t dstPortIndex;
};

EG_NS_END

#endif
