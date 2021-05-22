#ifndef H05B2224D_B926_4FC0_A936_97B52B8A98DB
#define H05B2224D_B926_4FC0_A936_97B52B8A98DB

#include "easy_graph/eg.h"

EG_NS_BEGIN

namespace details
{
   template<typename T>
   struct Interface
   {
      virtual ~Interface() {}
   };
}

#define INTERFACE(Intf)  struct Intf : ::EG_NS::details::Interface<Intf>

#define ABSTRACT(...) virtual __VA_ARGS__ = 0

#define OVERRIDE(...) virtual __VA_ARGS__ override

#define EXTENDS(...) , ##__VA_ARGS__
#define IMPLEMENTS(...) EXTENDS(__VA_ARGS__)

EG_NS_END

#endif

