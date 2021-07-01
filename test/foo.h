#pragma once

// https://stackoverflow.com/questions/51863588/warning-definition-of-implicit-copy-constructor-is-deprecated
// see note about rule of three
template <typename T>
struct Foo {
    int* m_id;
    Foo() : m_id(new int(-1)) {}
    Foo(int id) {
        m_id = new int(id);
    }
    Foo(const Foo<T>& rhs) {
        m_id = new int(*rhs.m_id);
    }
    Foo(const Foo<T>* rhs) {
        m_id = new int(*rhs->m_id);
    }
    ~Foo() {
        if (m_id != nullptr) {
            delete m_id;
        }
    }
    Foo<T>& operator=(const Foo<T>& rhs) {
        *this->m_id = *rhs.m_id;
        return *this;
    }
    bool operator==(const Foo<T>& rhs) const {
        return *m_id == *rhs.m_id;
    }
    bool operator==(int id) const {
        return *m_id == id;
    }
    bool operator<(const Foo<T>& rhs) const {
        return this->ID() < rhs.ID();
    }
    int ID() const {
        return *m_id;
    }
};

template <typename T>
inline bool operator==(int id, const Foo<T>& rhs) {
    return *rhs.m_id == id;
}