#pragma once 

#include <iostream>
#include <memory>
#include <list>
#include <deque>

using std::deque;

namespace new_Allocator{
    template <class T, size_t BLOCK_SIZE = 50000>
    class Allocator{
        public:
            static constexpr size_t max_count = BLOCK_SIZE;
            using value_type = T;
            using pointer = T *;
            using const_pointer = const T *;
            Allocator(){
                _used_blocks.resize(max_count);
                // std::cout << "Start\n";
                for(size_t i{0}; i < max_count; i++){
                    _free_blocks.push_back(&(_used_blocks[i]));
                }
                _free_count = max_count;
            }
            ~Allocator(){
                if(_free_count < max_count){
                    std::cerr << "deallocate all blocks first\n"; 
                }
                _used_blocks.clear();
            }
            template <class U>
            struct rebind {
                using other = Allocator<U>;
            };
            pointer allocate(size_t n = 1){
                pointer result = nullptr;
                if(_free_count > 0){
                    // std::cout << "Dobby get on work\n";
                    result = _free_blocks.front();
                    _free_blocks.pop_front();
                    _free_count--;
                }
                else throw std::bad_alloc();
                return result;
            }
            void deallocate(pointer dobby, size_t n = 1) noexcept{
                bool check = false;
                pointer _start = &_used_blocks.front();
                pointer _end = &_used_blocks.back();
                if((pointer)dobby >= _start and (pointer)dobby <= _end){
                    for(auto elem : _free_blocks){
                        if((pointer)dobby == elem){
                            std::cerr << "already free\n";
                            return;
                        }
                    }
                    check = true;
                }
                if(_free_count < max_count and check){
                    // std::cout << "Dobby is free\n"
                    _free_blocks.push_back(dobby);
                    _free_count++; 
                }else{
                    std::cerr << "problem with adresses\n";
                }
            }
            template <typename U, typename... Args>
            void construct(U* p, Args &&...args) {
                pointer _start = &_used_blocks.front();
                pointer _end = &_used_blocks.back();
                if((pointer)p < _start or (pointer)p > _end){
                    throw std::invalid_argument("constructor error: invalid pointer (no access)\n");
                }else{
                    for(auto elem : _free_blocks){
                        if(elem == (pointer)p){
                            throw std::invalid_argument("constructor error: invalid pointer (already free)\n");
                        }
                    }
                    new (p) U(std::forward<Args>(args)...);
                }

            }
            void destroy(pointer p) {
                p->~T();
            }

        private:
            size_t _free_count;
            deque<value_type> _used_blocks;
            deque<pointer> _free_blocks;
    };

    template <class T, class U>
    constexpr bool operator==(const Allocator<T> &lhs, const Allocator<U> &rhs) {
        return &lhs == &rhs;
    }

    template <typename T, typename U, size_t BLOCK_COUNT>
    constexpr bool operator!=(const Allocator<T> &lhs, const Allocator<U> &rhs) {
        return not(lhs == rhs);
    }
};