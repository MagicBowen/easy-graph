#ifndef HA25033D6_1564_4748_B2C8_4DE2C5A286DE
#define HA25033D6_1564_4748_B2C8_4DE2C5A286DE

#include "easy_graph/eg.h"

EG_NS_BEGIN

enum class Status {
	SUCCESS = 0,

	RESERVED_FAIL = -1,
	FAILURE       = -2,
	FATAL_BUG     = -3,
	TIMEDOUT      = -4,
	OUT_OF_RANGE  = -5,
	UNIMPLEMENTED = -6,
};

static inline bool eg_status_ok(Status status)
{
    return (status > Status::RESERVED_FAIL);
}

static inline bool eg_status_failed(Status status)
{
    return !eg_status_ok(status);
}

EG_NS_END

#endif
