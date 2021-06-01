#ifndef H37156CC2_92BD_44DA_8DA7_A11629E762BE
#define H37156CC2_92BD_44DA_8DA7_A11629E762BE

#include "easy_graph/layout/layout_option.h"
#include <string>

EG_NS_BEGIN

enum class FlowDir {
	LR = 0,
	TB,
};

enum class LayoutType {
	FREE = 0,
	REGULAR,
};

enum class LayoutFormat {
	ASCII = 0,
	BOXART,
	SVG,
	DOT,
	HTML,
};

enum class LayoutOutput {
	CONSOLE = 0,
	FILE,
};

struct GraphEasyOption : LayoutOption {

	static const GraphEasyOption& getDefault();

	std::string getLayoutCmdArgs(const std::string& graphName) const;

	LayoutFormat format{LayoutFormat::BOXART};
	LayoutOutput output{LayoutOutput::CONSOLE};
	FlowDir dir{FlowDir::LR};
	LayoutType type{LayoutType::FREE};
	size_t scale{1};
	std::string outputPath{"./"};
};

EG_NS_END

#endif
