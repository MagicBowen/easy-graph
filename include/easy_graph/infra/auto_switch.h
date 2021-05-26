#ifndef H187A4A00_BD91_4B9D_8DD9_3D6C9EA15854
#define H187A4A00_BD91_4B9D_8DD9_3D6C9EA15854

#include "easy_graph/eg.h"

EG_NS_BEGIN

template<typename BEGIN, typename END>
struct AutoSwitch {
	AutoSwitch(BEGIN begin, END end)
	: begin(begin), end(end) {
		begin();
	}

	~AutoSwitch() {
		end();
	}

private:
	BEGIN begin;
	END end;
};

EG_NS_END

#endif
