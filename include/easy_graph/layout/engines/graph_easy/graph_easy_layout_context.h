#ifndef HB8CC77BE_6A2E_4EB4_BE59_CA85DE56C027
#define HB8CC77BE_6A2E_4EB4_BE59_CA85DE56C027

#include "easy_graph/eg.h"
#include <string>
#include <deque>

EG_NS_BEGIN

struct GraphEasyOption;
struct Graph;

struct GraphEasyLayoutContext {
	GraphEasyLayoutContext(const GraphEasyOption&);

	void enterGraph(const Graph&);
	void exitGraph();

	std::string getGroupPath() const;
	const Graph* getCurrentGraph() const;

	const GraphEasyOption& getOptions() const;

private:
	std::deque<const Graph*> graphs;
	const GraphEasyOption& options;
};

EG_NS_END

#endif
