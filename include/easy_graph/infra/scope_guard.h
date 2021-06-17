#ifndef H187A4A00_BD91_4B9D_8DD9_3D6C9EA15854
#define H187A4A00_BD91_4B9D_8DD9_3D6C9EA15854

#include "easy_graph/eg.h"
#include "easy_graph/infra/symbol.h"

EG_NS_BEGIN

template<typename BEGIN, typename END>
struct ScopeGuard {
	ScopeGuard(BEGIN begin, END end)
	: begin(begin), end(end) {
		begin();
	}

	~ScopeGuard() {
		end();
	}

private:
	BEGIN begin;
	END end;
};

#define AUTO_GUARD(...)  ScopeGuard UNIQUE_NAME(guard_){__VA_ARGS__}

EG_NS_END

#endif
