#include <iostream>
#include <map>
#include <list>
#include "include/allocator.hpp"
#include "include/list.hpp"

using namespace new_Allocator;
using std::cin;
using std::cout;
using std::cerr;
using std::exception;
using std::endl;
using std::pair;
using std::less;
using std::map;

unsigned long long int factorial(int n) {
	if (n > 0) {
		return n * factorial(n - 1);
	}
	return 1;
}


int main()
{
    try{
        // std::map<int, int, std::less<int>, Allocator<std::pair<const int,int>>> my_map;
        // int res = 1;
        // for (size_t i = 0; i < 5; ++i) {
        //     res = 1;
        //     for (size_t j = 1; j <= i; ++j) {
        //     res *= j;
        //     }
        //     my_map[i] = res;
        // }

        // for(const auto& [k,v]: my_map) {
        //     cout << k << " -> " << v << endl;
        // }

        cout << "List test\n";

        List<int, Allocator<int>> lst;

        cout << "Size: " << lst.size() << endl;

        for(size_t i{0}; i < 6; ++i){
            lst.emplace_back(factorial(i));
        }

        cout << "Size: " << lst.size() << endl;

        size_t i {0};

        cout << "test iterator and emplace by iterator\n";

        List<int, Allocator<int>>::Iterator spec;

        for(List<int, Allocator<int>>::Iterator it = lst.begin(); it != lst.end(); ++it){
            cout << i++ << " -> " << *it << endl;
            if(i == 2){
                spec = it;
            }
        }

        lst.emplace(spec, 77);

        cout << "list after emplace to it on i = 1\n";

        i = 0;
        cout << "Size: " << lst.size() << endl;

        for(List<int, Allocator<int>>::Iterator it = lst.begin(); it != lst.end(); ++it){
            cout << i++ << " -> " << *it << endl;
        }

        i = 0;
        cout << "Clean list\n";

        lst.erase(spec); cout << "Delete special (2nd) element\n";

        // while(!lst.empty()){
        //     cout << i++ << " -> " << lst.begin() << endl;
        //     lst.erase(lst.begin());
        // }

        lst.clear();

        cout << "Size: " << lst.size() << endl;

    }catch(exception &ex){ cerr << ex.what() << endl;}
    return 0;
}
