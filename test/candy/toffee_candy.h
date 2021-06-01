#ifndef HCFDE34FF_6916_4F81_9B4C_764E76A7A53D
#define HCFDE34FF_6916_4F81_9B4C_764E76A7A53D

#include "candy/candy.h"

EG_NS_BEGIN

struct ToffeeCandy : Candy {
	ToffeeCandy(const std::string& label) : label(label) {
	}

	std::string getLabel() const override {
		return std::string("Toffee (Label:") + label + ")";
	}

private:
	std::string label;
};

EG_NS_END

#endif
