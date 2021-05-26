#ifndef HD18A3E42_2801_4BEB_B365_03633D1D81C4
#define HD18A3E42_2801_4BEB_B365_03633D1D81C4

#include "easy_graph/eg.h"

EG_NS_BEGIN

template<typename T>
struct Singleton
{
    static T& getInstance()
    {
        static T instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator = (const Singleton&) = delete;

protected:
    Singleton() {}
};

#define SINGLETON(object) struct object : ::EG_NS::Singleton<object>


EG_NS_END

#endif
