#include "layout_context.h"
#include "layout_option.h"

EG_NS_BEGIN

LayoutContext::LayoutContext(const std::string& root, const LayoutOption& options)
: root(root), options(options){
}

void LayoutContext::enterGroup(const std::string& groupName) {
	groups.push_back(groupName);
}

void LayoutContext::exitGroup() {
	groups.pop_back();
}

void LayoutContext::linkBegin() {
	isLinking = true;
}

void LayoutContext::linkEnd(){
	isLinking = false;
}

bool LayoutContext::inLinking() const {
	return isLinking;
}

std::string LayoutContext::getGroupPath() const {
	if (groups.empty()) return "";
	std::string result("");
	std::for_each(groups.begin(), groups.end(), [&result](const auto& group) {
		result += (std::string("/") + group);
	});
	return (result + "/");
}

const LayoutOption& LayoutContext::getOptions() const {
	return options;
}

EG_NS_END
