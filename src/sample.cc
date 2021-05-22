namespace {
    template<typename T> constexpr auto PI = static_cast<T>(3.1415926);
}

int getPI(int x) {
    return PI<int>;
}