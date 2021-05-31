#ifndef HC2BC572B_3C3F_48BD_ADCD_E3E4C9511CBA
#define HC2BC572B_3C3F_48BD_ADCD_E3E4C9511CBA

#include "candy/candy.h"

EG_NS_BEGIN

struct Integer : Candy {
	Integer(int id = 0) : id(id) {
	}

	std::string getLabel() const override {
		return std::to_string(id);
	}

private:
	int id;
};

EG_NS_END

#endif
