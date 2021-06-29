#pragma once

template <typename T>
struct Option {
    Option() : result(None) {}
    // Option(const T& val) : result(Some), value(val) {}
    operator T() { return value; }
    enum Result { None,
                  Some };
    Result result;
    T value;
};

// here's what the other guy wrote https://codereview.stackexchange.com/questions/175882/optionalt-implementation
// a little simpler https://github.com/martinmoene/optional-bare/blob/master/include/nonstd/optional.hpp
