#include "easy_graph/checker/check_error.h"

EG_NS_BEGIN

CheckError::CheckError(const char* file, int line, const std::string& info) {
	this->info = std::string(file) + ":" + std::to_string(line) + "\n" + info;
}

const char* CheckError::what() const noexcept {
	return info.c_str();
}

EG_NS_END
