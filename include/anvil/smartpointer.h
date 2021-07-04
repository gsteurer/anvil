#pragma once
#include <stddef.h>

#include "anvil/types.h"
// https://www.learncpp.com/cpp-tutorial/intro-to-smart-pointers-move-semantics/

namespace anvil {
namespace internal {
// dont use auto pointer because:
// passing by value to a function causes the pointer to be deleted when the function exits (unless of course it is returned from the function)
// always deletes its contents using non array delete making it incompatible and unusable with arrays
// classes that assume that when a copy is made, something gets copied. not moved.
// however this is compatible with c++ before c++11 @@@ is this true?
template <typename T>
struct AutoPointer {
    AutoPointer() = delete;
    AutoPointer(T* pointer) {
        m_pointer = pointer;
    }
    ~AutoPointer() { delete m_pointer; }
    AutoPointer(const AutoPointer&) = delete;
    AutoPointer& operator=(const AutoPointer&) = delete;

    // move semantics
    AutoPointer(AutoPointer& a) {
        m_pointer = a.m_pointer;
        a.m_pointer = nullptr;
    }
    AutoPointer& operator=(AutoPointer& a) {
        if (&a == this)
            return *this;

        delete m_pointer;
        m_pointer = a.m_pointer;
        a.m_pointer = nullptr;

        return *this;
    }
    T& operator*() const {
        return *m_pointer;
    }
    T* operator->() const {
        if (m_pointer != nullptr)
            return m_pointer;
    }
    void* operator new(size_t) = delete;
    void operator delete(void*) = delete;

    bool IsNull() const {
        return m_pointer == nullptr;
    }

   private:
    T* m_pointer;
};
};  // namespace internal

struct UniquePointer {
};

struct SharedPointer {
};

}  // namespace anvil