#ifndef HEAD64603_8E9E_4E3B_8672_BF74E8E110DC
#define HEAD64603_8E9E_4E3B_8672_BF74E8E110DC

#include "layoutable.h"
#include "keywords.h"
#include "layout_context.h"
#include <string>

EG_NS_BEGIN

template<typename VISITOR, typename ITEM>
struct LayoutVisitor : VISITOR {
	LayoutVisitor(LayoutContext& context)
	: context(context) {
	}

	std::string layout;

private:
	OVERRIDE(void visit(const ITEM& item)) {
	    if constexpr (std::is_same<ITEM, Edge>::value) {
	    	context.linkBegin();
	    }
	    else {
	    	context.linkEnd();
	    }
		const Layoutable& layoutable = item;
		layout += layoutable.getLayout(context);
	}

private:
	LayoutContext& context;
};

EG_NS_END

#endif
