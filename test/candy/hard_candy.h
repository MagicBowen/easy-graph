#ifndef HC2BC572B_3C3F_48BD_ADCD_E3E4C9511CBA
#define HC2BC572B_3C3F_48BD_ADCD_E3E4C9511CBA

#include "candy/candy.h"

EG_NS_BEGIN

struct HardCandy : Candy {
	HardCandy(int level = 0) : hardLevel(level) {
	}

	std::string getLabel() const override {
		return std::string("Hard Candy (Level:") + std::to_string(hardLevel) + ")";
	}

private:
	int hardLevel;
};

EG_NS_END

#endif
