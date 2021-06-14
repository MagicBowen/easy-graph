#ifndef H4AA49861_3311_4114_8687_1C7D04FA43B9
#define H4AA49861_3311_4114_8687_1C7D04FA43B9

#include "easy_graph/infra/keywords.h"
#include <memory>

EG_NS_BEGIN

INTERFACE(Box) {
};

using BoxPtr = std::shared_ptr<Box>;

template<typename ANYTHING, typename ...ARGS>
BoxPtr box_packing(ARGS && ...args) {
	return std::make_shared<ANYTHING>(std::forward<ARGS>(args)...);
}

template<typename ANYTHING>
auto box_unpacking(const BoxPtr& box) {
	return dynamic_cast<ANYTHING*>(box.get());
}

EG_NS_END

#endif
