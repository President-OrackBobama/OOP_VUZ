#include <memory>
#include "../include/Vector.hpp"

template<typename T>
Vector<T>::Vector() {
    arr = reinterpret_cast<T*>(new char[sizeof(T)]);
}

template<typename T>
void Vector<T>::reserve(const size_t& n) {
    if (n < cap) return;
    T* new_arr = reinterpret_cast<T*>(new char[n * sizeof(T)]);
    try {
        std::uninitialized_copy(arr, arr + sz, new_arr);
    } catch(...) {
        delete[] reinterpret_cast<char*>(new_arr);
        throw;
    }
    for(size_t i = 0; i < sz; ++i){
        arr[i].~T();
    }
    delete[] reinterpret_cast<char*>(arr);
    arr = new_arr;
    cap = n;
}

template<typename T>
void Vector<T>::resize(const size_t n, const T& value){
    if (sz > n) {
        for (size_t i = n; i < sz; ++i){
            arr[i].~T();
        }
        sz = n;
        return;
    }

    if (n > this->cap){
        reserve(n * 2);
    }

    for (size_t i = this->sz; i < n; ++i){
        new(arr + i) T(value);
    }
    sz = n;
}

template<typename T>
void Vector<T>::push_back(const T& value){
    if (cap == sz){
        reserve(2 * cap);
    }
    new(arr + sz) T(value);
    ++sz;
}

template<typename T>
template<typename... Args>
void Vector<T>::emplace_back(const T &First, const Args &...args)
{
    push_back(First);
    emplace_back(args...);
}

template<typename T>
void Vector<T>::emplace_back(){}

template<typename T>
void Vector<T>::pop_back(){
    if (sz > 0) {
        --sz;
        arr[sz].~T();
    }
}

template<typename T>
T& Vector<T>::at(const size_t &index) {
    if (0 <= index and index < sz) {
        return *(arr + index);
    } else {
        throw std::out_of_range("Invalid index");
    }
}

template<typename T>
T& Vector<T>::operator[](const size_t& index) {
    return arr[index];
}

template<typename T>
T& Vector<T>::operator[](const size_t& index) const {
    return arr[index];
}

template<typename T>
T& Vector<T>::front() {
    return *arr;
}

template<typename T>
T& Vector<T>::back() {
    return *(arr + sz - 1);
}

template<typename T>
bool Vector<T>::empty() const {
    return sz == 0;
}

template<typename T>
size_t Vector<T>::size() const {
    return sz;
}

template<typename T>
size_t Vector<T>::capacity() const {
    return cap;
}

template<typename T>
void Vector<T>::shrink_to_fit() {
    for (size_t i = sz; i < cap; ++i){
        arr[i].~T();
    }
    cap = sz;
    if (cap == 0) {
        cap = 1;
    }
}

template<typename T>
void Vector<T>::clear() {
    for (size_t i = 0; i < cap; ++i){
        arr[i].~T();
    }
    sz = 0;
}

template<typename T>
void Vector<T>::erase(size_t index) {
    if (index >= sz) {
        throw std::out_of_range("Invalid index, it's bigger than size");
    }
    if (!sz) {
        return;
    }
    if (index == sz - 1) {
        pop_back();
        return;
    }
    arr[index].~T();
    for (size_t i = index; i <= sz - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    pop_back();
}

template<typename T>
Vector<T>::Vector(const Vector<T> &old_vector) {
    sz = old_vector.sz;
    cap = old_vector.cap;
    T *new_arr = reinterpret_cast<T*>(new int8_t[cap * sizeof(T)]);

    try {
        std::uninitialized_copy(old_vector.arr, old_vector.arr + old_vector.sz, new_arr);
    } catch (...) {
        delete[] reinterpret_cast<char *>(new_arr);
        throw;
    }
    arr = new_arr;
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> init) {
    T* new_arr = reinterpret_cast<T*>(new int8_t[init.size() * sizeof(T)]);
    try {
        std::uninitialized_copy(init.begin(), init.end(), new_arr);
    } catch (...) {
        delete[] reinterpret_cast<char *>(new_arr);
        throw;
    }
    arr = new_arr;
    cap = init.size();
    sz = init.size();
}

template<typename T>
bool Vector<T>::operator==(Vector<T> &x) {
    if (sz != x.sz)
        return false;
    for (size_t i = 0; i < sz; ++i) {
        if (arr[i] != x.arr[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Vector<T>::operator!=(Vector<T> &x) {
    return not (*this == x);
}

template<typename T>
Vector<T>::~Vector() {
    for (size_t i = 0; i < sz; ++i) {
        arr[i].~T();
    }
    delete[] reinterpret_cast<char*>(arr);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this == &other){
        return *this;
    }

    this->resize(other.size());
    for (size_t i = 0; i < sz; ++i){
        arr[i].~T();
        new(arr + i) T(other.arr[i]);
    }

    return *this;
}
