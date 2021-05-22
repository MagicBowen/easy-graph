#ifndef HB141A993_B14A_4A1D_A1DD_353D33AE77A2
#define HB141A993_B14A_4A1D_A1DD_353D33AE77A2

#include "easy_graph/eg.h"
#include "easy_graph/status.h"
#include <string>

EG_NS_BEGIN

struct ShellExecutor {
	static Status execute(const std::string& script);
};

EG_NS_END

#endif
