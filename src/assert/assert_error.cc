#include "easy_graph/assert/assert_error.h"

EG_NS_BEGIN

AssertError::AssertError(const char* file, int line, const std::string& info) {
	this->info = std::string(file) + ":" + std::to_string(line) + "\n" + info;
}

const char* AssertError::what() const noexcept {
	return info.c_str();
}

EG_NS_END
