#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED

template <typename T>
class Vector {
private:
    size_t sz = 0;
    size_t cap = 1;
    T* arr;
public:
    Vector();
    ~Vector();

    void reserve(const size_t& n);
    void resize(size_t n, const T& value = T());
    void push_back(const T& value);
    void pop_back();
    void shrink_to_fit();
    void clear();
    void erase(size_t index);

    template<typename... Args>
    void emplace_back(const T &First, const Args &...args);
    void emplace_back();

    T& at(const size_t &index);
    T& operator[](const size_t &index);
    T& operator[](const size_t &index) const;
    T& front();
    T& back();

    bool empty() const;
    size_t size() const;
    size_t capacity() const;

    Vector<T>& operator=(const Vector<T> &other);
    bool operator==(Vector<T> &x);
    bool operator!=(Vector<T> &x);
    Vector(const Vector<T> &old_vector);
    Vector(std::initializer_list<T> init);

};


#endif
