#ifndef HB8CC77BE_6A2E_4EB4_BE59_CA85DE56C027
#define HB8CC77BE_6A2E_4EB4_BE59_CA85DE56C027

#include "easy_graph/eg.h"
#include <string>
#include <deque>

EG_NS_BEGIN

struct GraphEasyOption;

struct GraphEasyLayoutContext {
	GraphEasyLayoutContext(const GraphEasyOption&);

	void enterGroup(const std::string&);
	void exitGroup();

	void linkBegin();
	void linkEnd();
	bool inLinking() const;

	std::string getGroupPath() const;
	const GraphEasyOption& getOptions() const;

private:
	std::deque<std::string> groups;
	const GraphEasyOption& options;
	bool isLinking{false};
};

EG_NS_END

#endif
