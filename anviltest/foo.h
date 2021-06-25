#pragma once

// https://stackoverflow.com/questions/51863588/warning-definition-of-implicit-copy-constructor-is-deprecated
// see note about rule of three
template <typename T>
struct Foo {
    int* m_id;
    Foo();
    Foo(int id);
    Foo(const Foo<T>& rhs);
    Foo(const Foo<T>* rhs);
    ~Foo();
    Foo<T>& operator=(const Foo<T>& rhs);
    bool operator==(const Foo<T>& rhs) const;
    bool operator==(int id) const;
    int ID() const;
};

template <typename T>
Foo<T>::Foo() : m_id(new int(-1)) {}

template <typename T>
Foo<T>::Foo(int id) {
    m_id = new int(id);
}

template <typename T>
Foo<T>::Foo(const Foo<T>& rhs) {
    m_id = new int(*rhs.m_id);
}

template <typename T>
Foo<T>::Foo(const Foo<T>* rhs) {
    m_id = new int(*rhs->m_id);
}

template <typename T>
Foo<T>::~Foo() {
    if (m_id != nullptr) {
        delete m_id;
    }
}

template <typename T>
Foo<T>& Foo<T>::operator=(const Foo<T>& rhs) {
    *this->m_id = *rhs.m_id;
    return *this;
}

template <typename T>
bool Foo<T>::operator==(const Foo<T>& rhs) const {
    return *m_id == *rhs.m_id;
}

template <typename T>
bool Foo<T>::operator==(int id) const {
    return *m_id == id;
}

template <typename T>
int Foo<T>::ID() const {
    return *m_id;
}