#ifndef HB8CC77BE_6A2E_4EB4_BE59_CA85DE56C027
#define HB8CC77BE_6A2E_4EB4_BE59_CA85DE56C027

#include "easy_graph/eg.h"
#include <string>
#include <stack>

EG_NS_BEGIN

struct LayoutOption;

struct LayoutContext {
	LayoutContext(const std::string& root, const LayoutOption&);

	void enterGroup(const std::string&);
	void exitGroup();

	std::string getNamespace() const;

	const LayoutOption& getOptions() const;

private:
	std::stack<std::string> namespaces;
	const LayoutOption& options;
	std::string root;
};

EG_NS_END

#endif
