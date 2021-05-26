#include "easy_graph/layout/engines/graph_easy/graph_easy_layout_context.h"
#include "easy_graph/layout/engines/graph_easy/graph_easy_option.h"

EG_NS_BEGIN

GraphEasyLayoutContext::GraphEasyLayoutContext(const GraphEasyOption& options)
: options(options){
}

void GraphEasyLayoutContext::enterGroup(const std::string& groupName) {
	groups.push_back(groupName);
}

void GraphEasyLayoutContext::exitGroup() {
	groups.pop_back();
}

void GraphEasyLayoutContext::linkBegin() {
	isLinking = true;
}

void GraphEasyLayoutContext::linkEnd(){
	isLinking = false;
}

bool GraphEasyLayoutContext::inLinking() const {
	return isLinking;
}

std::string GraphEasyLayoutContext::getGroupPath() const {
	if (groups.empty()) return "";
	std::string result("");
	std::for_each(groups.begin(), groups.end(), [&result](const auto& group) {
		result += (std::string("/") + group);
	});
	return (result + "/");
}

const GraphEasyOption& GraphEasyLayoutContext::getOptions() const {
	return options;
}

EG_NS_END
