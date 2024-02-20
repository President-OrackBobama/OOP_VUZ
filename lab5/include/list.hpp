#pragma once

#include <iostream>
 
template <class T, class Allocator, int BLOCK_COUNT = 100>
class List{
    public:


        struct Node;
        using alloc = typename Allocator::template rebind<Node>::other;
        struct Node{
            T _data;
            Node* _next;
            Node* _prev;
            Node() noexcept : _data(), _next(nullptr), _prev(nullptr){}
            Node(const T& elem) noexcept : _data(elem), _next(nullptr), _prev(nullptr){}
            friend std::ostream & operator << (std::ostream & out, const Node & node) {
                out << node._data;
                return out;
            }
            friend bool operator == (const Node & lhs, const Node & rhs) {
                return &lhs._data == &rhs._data;
            }
        };


        struct eraser {
            alloc erase_elem;

            eraser() : erase_elem() {};
            eraser(alloc* another_eraser) : erase_elem(another_eraser) {}

            void operator() (void* ptr) {
                erase_elem.deallocate((Node*)ptr, 1);
            }
        };


        class Iterator{
            public:
                
                using difference_type = std::ptrdiff_t;
                using iterator_categoty = std::forward_iterator_tag;
                
                Iterator() : _cur_node(nullptr){}
                Iterator(Node* other) : _cur_node(other){}
                
                Iterator&  operator++(){
                    if(_cur_node){
                        _cur_node = _cur_node->_next;
                        return *this;
                    }else{
                        throw std::logic_error("Iterator points to nullptr");
                    }
                }
                Iterator&  operator--(){
                    if(_cur_node){
                        _cur_node = _cur_node->_prev;
                        return *this;
                    }else{
                        throw std::logic_error("Iterator points to nullptr");
                    }
                }
                bool operator!=(const Iterator & iter_oth){
                    return &iter_oth._cur_node->_data != &this->_cur_node->_data;
                }

                bool operator==(const Iterator & iter_oth){
                    return &iter_oth._cur_node->_data == &this->_cur_node->_data;
                }

                void operator=(const Iterator & iter_oth){
                    _cur_node = iter_oth._cur_node;
                }

                T& operator*(){
                    return _cur_node->_data;
                }

                friend std::ostream & operator << (std::ostream & out, const Iterator & it) {
                    out << *(it._cur_node);
                    return out;
                }
            // private:
                Node* _cur_node;
        };


        List() : _finish_node(nullptr), _start_node(nullptr){}
        void erase(Iterator it){
            if(it._cur_node){
                if(it._cur_node == _start_node){
                    _start_node = _start_node->_next;
                }
                if(it._cur_node == _finish_node){
                    _finish_node = _finish_node->_prev;
                }

                if(it._cur_node->_next and it._cur_node->_prev){
                    it._cur_node->_prev->_next = it._cur_node->_next;
                    it._cur_node->_next->_prev = it._cur_node->_prev;
                }
                else if(it._cur_node->_next){
                    it._cur_node->_next->_prev = nullptr;
                }
                else if(it._cur_node->_prev){
                    it._cur_node->_prev->_next = nullptr;
                }
                erase_l.erase_elem.deallocate(it._cur_node, 1);
            
            }else throw std::logic_error("No elem!");
        }
        void emplace(Iterator it, T val){
            if(it._cur_node){
                Node* new_elem = erase_l.erase_elem.allocate(sizeof(Node));
                erase_l.erase_elem.construct(new_elem, val);
                Node* new_element(new_elem);

                new_element->_prev = it._cur_node->_prev;
                new_element->_next = it._cur_node;
                if (it._cur_node->_prev) it._cur_node->_prev->_next = new_element;
                it._cur_node->_prev = new_element;
            }else{
                throw std::logic_error("No place to emplace!");
            }
        }
        void emplace_front(T val){
            Node* new_elem = erase_l.erase_elem.allocate(sizeof(Node));
            erase_l.erase_elem.construct(new_elem, val);
            Node* new_element(new_elem);
            if (!(_start_node)){
                _start_node = new_element;
                _finish_node = new_element;
            }
            else{
                _start_node->_prev = new_element;
                new_element->_next = _start_node;
                new_element->_prev = nullptr;
                _start_node = new_element;
            }
        }
        void emplace_back(T val){
            Node* new_elem = erase_l.erase_elem.allocate(sizeof(Node));
            erase_l.erase_elem.construct(new_elem, val);
            Node* new_element(new_elem);
            if (!(_finish_node)){
                _start_node = new_element;
                _finish_node = new_element;
            }
            else{
                _finish_node->_next = new_element;
                new_element->_prev = _finish_node;
                new_element->_next = nullptr;
                _finish_node = new_element;
            }
        }
        size_t size(){
            size_t _size{0};
            if(_start_node){
                Node* position = _start_node;
                while(position){
                    _size++;
                    position = position->_next;
                }
            }
            return _size;
        }
        Iterator begin() const {
            return Iterator(_start_node);
        }
        Iterator end() const {
            return Iterator(_finish_node->_next);
        }
        Iterator rbegin(){
            return Iterator(_finish_node);
        }
        Iterator rend(){
            return Iterator(_start_node->_prev);
        }
        bool empty() const {
            return (_start_node == nullptr);
        }
        T front() const {
            return _start_node->_data;
        }
        T back() const {
            return _finish_node->_data;
        }
        void clear() noexcept {
            while(!this->empty()){
                this->erase(this->begin());
            }
        }
    private:
        Node* _finish_node;
        Node* _start_node;
        eraser erase_l;
};