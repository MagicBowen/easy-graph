#ifndef HA25033D6_1564_4748_B2C8_4DE2C5A286DE
#define HA25033D6_1564_4748_B2C8_4DE2C5A286DE

#include "easy_graph/eg.h"
#include <stdbool.h>
#include <stdint.h>

EG_NS_BEGIN

using Status = uint32_t;

#define EG_SUCC_STATUS(status) (EG_NS::Status) status
#define EG_FAIL_STATUS(status) (EG_NS::Status) (status | EG_RESERVED_FAIL)


/* OK */
#define EG_SUCCESS              EG_SUCC_STATUS(0)

/* Error Status */
#define EG_RESERVED_FAIL       (EG_NS::Status) 0x80000000
#define EG_FAILURE             EG_FAIL_STATUS(1)
#define EG_FATAL_BUG           EG_FAIL_STATUS(2)
#define EG_TIMEDOUT            EG_FAIL_STATUS(3)
#define EG_OUT_OF_RANGE        EG_FAIL_STATUS(4)
#define EG_UNIMPLEMENTED       EG_FAIL_STATUS(5)

static inline bool eg_status_is_ok(Status status)
{
    return (status & EG_RESERVED_FAIL) == 0;
}

static inline bool eg_status_is_fail(Status status)
{
    return !eg_status_is_ok(status);
}

#define __EG_FAILED(result)   eg_status_is_fail(result)
#define __EG_OK(result)       eg_status_is_ok(result)

EG_NS_END

#endif
