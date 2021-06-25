#ifndef HCCCD4F7B_C64A_4788_B164_C5AE7AA78997
#define HCCCD4F7B_C64A_4788_B164_C5AE7AA78997

#include "easy_graph/eg.h"
#include <exception>
#include <string>

EG_NS_BEGIN

struct CheckError : std::exception {
	CheckError(const char* file, int line, const std::string& info);

private:
	const char* what() const noexcept override;

private:
	std::string info;
};

EG_NS_END

#endif
