#ifndef H49EDB46E_ECF2_450D_899D_62318011BD1B
#define H49EDB46E_ECF2_450D_899D_62318011BD1B

#include "easy_graph/infra/keywords.h"
#include <string>
#include <array>

EG_NS_BEGIN

///////////////////////////////////////////////////////////////
INTERFACE(Candy) {
	ABSTRACT(std::string getLabel() const);
};

///////////////////////////////////////////////////////////////
struct ToffeeCandy : Candy {
	ToffeeCandy(const std::string& label) : label(label) {
	}

private:
	std::string getLabel() const override {
		return std::string("Toffee (Label:") + label + ")";
	}

private:
	std::string label;
};

///////////////////////////////////////////////////////////////
struct HardCandy : Candy {
	HardCandy(int level = 0) : hardLevel(level) {
	}

private:
	std::string getLabel() const override {
		return std::string("Hard Candy (Level:") + std::to_string(hardLevel) + ")";
	}

private:
	int hardLevel;
};

///////////////////////////////////////////////////////////////
struct JellyCandy : Candy {
	enum Shape{
		TRIANGLE,
		RECTANGLE,
		CIRCLE,
	};

	JellyCandy(Shape type) : type(type) {
	}

private:
	std::string getLabel() const override {
		std::string jellyType;
		switch (type) {
		case Shape::TRIANGLE  : jellyType = "Triangle"; break;
		case Shape::RECTANGLE : jellyType = "Rectangle"; break;
		case Shape::CIRCLE    : jellyType = "Circle"; break;
		default: jellyType = "None";
		}
		return std::string("Jelly (Shape:") + jellyType + ")";
	}

private:
	Shape type;
};

///////////////////////////////////////////////////////////////
struct ColorCandy : Candy {
	ColorCandy(size_t r, size_t g, size_t b)
	: rgb{r, g, b}{
	}

private:
	std::string getLabel() const override {
		return std::string("Color Candy (") +
				 "R:" + std::to_string(rgb[0]) +
				",G:" + std::to_string(rgb[1]) +
				",B:" + std::to_string(rgb[2]) +
				")";
	}

private:
	std::array<size_t, 3> rgb;
};

EG_NS_END

#endif
