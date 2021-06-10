#pragma once

template <typename T>
struct Option {
    enum Result { None,
                  Some };
    Result result;
    T value;
};

// here's what the other guy wrote https://codereview.stackexchange.com/questions/175882/optionalt-implementation
