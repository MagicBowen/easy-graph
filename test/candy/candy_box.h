#ifndef HE877DBC0_B5F0_4ECC_A814_57BFC60DC26A
#define HE877DBC0_B5F0_4ECC_A814_57BFC60DC26A

#include "easy_graph/builder/box_builder.h"

EG_NS_BEGIN

#define CANDY(TYPE, ...)      BOXING(TYPE, getLabel, __VA_ARGS__)
#define CANDY_NODE(TYPE, ...) NODE(CANDY(TYPE, __VA_ARGS__))

EG_NS_END

#endif
