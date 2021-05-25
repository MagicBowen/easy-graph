#ifndef HEAD64603_8E9E_4E3B_8672_BF74E8E110DC
#define HEAD64603_8E9E_4E3B_8672_BF74E8E110DC

#include "layoutable.h"
#include "keywords.h"
#include <string>

EG_NS_BEGIN

struct LayoutOption;

template<typename VISITOR, typename ITEM>
struct LayoutVisitor : VISITOR {
	LayoutVisitor(const LayoutOption& options)
	: options(options) {
	}

	std::string layout;

private:
	OVERRIDE(void visit(const ITEM& item)) {
		const Layoutable& layoutable = item;
		layout += layoutable.getLayout(options);
	}

private:
	const LayoutOption& options;
};

EG_NS_END

#endif
