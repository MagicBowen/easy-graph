#ifndef H9577A410_3CEB_4AA0_952B_92E994C09881
#define H9577A410_3CEB_4AA0_952B_92E994C09881

#include "candy/candy.h"

EG_NS_BEGIN

enum class ShapeType{
	POINT,
	LINE,
	RECT,
	CIRCLE,
};

struct Shape : Candy {
	Shape(ShapeType type) : type(type) {
	}

	std::string getLabel() const override {
		switch (type) {
		case ShapeType::POINT :  return "point";
		case ShapeType::LINE :   return "line";
		case ShapeType::RECT :   return "rect";
		case ShapeType::CIRCLE : return "circle";
		}
		return "shape";
	}

private:
	ShapeType type;
};

EG_NS_END

#endif
