#ifndef HF1B366C0_AEC4_43E4_8231_DEE20D1044F7
#define HF1B366C0_AEC4_43E4_8231_DEE20D1044F7

#include "easy_graph/infra/log/log_print.h"

EG_NS_BEGIN

#define EG_FATAL(fmt, ...) LOG_FATAL(fmt, ##__VA_ARGS__)
#define EG_ERR(fmt, ...)   LOG_ERROR(fmt, ##__VA_ARGS__)
#define EG_WARN(fmt, ...)  LOG_WARN(fmt, ##__VA_ARGS__)
#define EG_SUCC(fmt, ...)  LOG_SUCC(fmt, ##__VA_ARGS__)
#define EG_INFO(fmt, ...)  LOG_INFO(fmt, ##__VA_ARGS__)
#define EG_DBG(fmt, ...)   LOG_DEBUG(fmt, ##__VA_ARGS__)

EG_NS_END

#endif
