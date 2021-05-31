#ifndef HFBD23167_86A8_4F39_8C97_F966B8376F52
#define HFBD23167_86A8_4F39_8C97_F966B8376F52

#include "candy/candy.h"
#include <array>

EG_NS_BEGIN

struct Color : Candy {
	Color(size_t r, size_t g, size_t b)
	: rgb{r, g, b}{
	}

	std::string getLabel() const override {
		return std::string("Color(") +
				"R:" + std::to_string(rgb[0]) +
				"G:" + std::to_string(rgb[1]) +
				"B:" + std::to_string(rgb[2]) +
				")";
	}

private:
	std::array<size_t, 3> rgb;
};

EG_NS_END

#endif
