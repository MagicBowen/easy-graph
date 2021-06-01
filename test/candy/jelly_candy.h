#ifndef H9577A410_3CEB_4AA0_952B_92E994C09881
#define H9577A410_3CEB_4AA0_952B_92E994C09881

#include "candy/candy.h"

EG_NS_BEGIN

enum class JellyType{
	TRIANGLE,
	RECTANGLE,
	CIRCLE,
};

struct JellyCandy : Candy {
	JellyCandy(JellyType type) : type(type) {
	}

	std::string getLabel() const override {
		std::string jellyType;
		switch (type) {
		case JellyType::TRIANGLE  : jellyType = "Triangle"; break;
		case JellyType::RECTANGLE : jellyType = "Rectangle"; break;
		case JellyType::CIRCLE    : jellyType = "Circle"; break;
		default: jellyType = "None";
		}
		return std::string("Jelly (Shape:") + jellyType + ")";
	}

private:
	JellyType type;
};

EG_NS_END

#endif
