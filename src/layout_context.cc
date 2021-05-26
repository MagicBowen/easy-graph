#include "layout_context.h"
#include "layout_option.h"

EG_NS_BEGIN

LayoutContext::LayoutContext(const std::string& root, const LayoutOption& options)
: root(root), options(options){
}

void LayoutContext::enterGroup(const std::string& groupName) {
	namespaces.push(groupName);
}

void LayoutContext::exitGroup() {
	namespaces.pop();
}

std::string LayoutContext::getNamespace() const {
	return root;
}

const LayoutOption& LayoutContext::getOptions() const {
	return options;
}

EG_NS_END
