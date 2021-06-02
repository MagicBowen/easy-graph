#ifndef HDF29CB40_B63F_4172_84CD_ED3841D3EA31
#define HDF29CB40_B63F_4172_84CD_ED3841D3EA31

#include "easy_graph/infra/singleton.h"

EG_NS_BEGIN

SINGLETON(IdGenerator) {
	unsigned int generate() {
		return id++;
	}

	void reset() {
		id = 0;
	}
private:
	unsigned int id{0};
};

EG_NS_END

#endif
