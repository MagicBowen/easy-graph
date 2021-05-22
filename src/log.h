#ifndef H38247538_297F_4A80_94D3_8A289788461B
#define H38247538_297F_4A80_94D3_8A289788461B

#include "easy_graph/eg.h"

EG_NS_BEGIN

enum EgLogLevel
{
	EG_NONE_LEVEL  = 0x0,
    EG_DEBUG_LEVEL = 0x01,
	EG_INFO_LEVEL  = 0x02,
	EG_SUCC_LEVEL  = 0x04,
	EG_WARN_LEVEL  = 0x08,
	EG_ERR_LEVEL   = 0x10,
	EG_FATAL_LEVEL = 0x20,
	EG_TOTAL_LEVEL = 0xFF
};

void eg_log(int level , const char* levelstr , const char* file, unsigned int line, const char* fmt, ...);


#define EG_LOG_OUTPUT eg_log

#define EG_LOG_LEVELS EG_TOTAL_LEVEL

#define __EG_LOG_TITLE(level, levelstr, fmt, ...) 		\
do {													\
	if (level & EG_LOG_LEVELS) {						\
		EG_LOG_OUTPUT(level, levelstr, __FILE__, __LINE__, fmt, ##__VA_ARGS__);\
	}										            \
} while(0)

#define EG_FATAL(fmt, ...) \
	__EG_LOG_TITLE(EG_FATAL_LEVEL, "FATAL", fmt, ##__VA_ARGS__)

#define EG_ERR(fmt, ...) \
	__EG_LOG_TITLE(EG_ERR_LEVEL  , "ERROR", fmt, ##__VA_ARGS__)

#define EG_WARN(fmt, ...) \
	__EG_LOG_TITLE(EG_WARN_LEVEL , "WARN" , fmt, ##__VA_ARGS__)

#define EG_SUCC(fmt, ...) \
	__EG_LOG_TITLE(EG_SUCC_LEVEL , "SUCC" , fmt, ##__VA_ARGS__)

#define EG_INFO(fmt, ...) \
	__EG_LOG_TITLE(EG_INFO_LEVEL , "INFO" , fmt, ##__VA_ARGS__)

#define EG_DBG(fmt, ...) \
	__EG_LOG_TITLE(EG_DEBUG_LEVEL, "DEBUG", fmt, ##__VA_ARGS__)

EG_NS_END

#endif
