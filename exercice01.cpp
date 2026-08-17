#include <iostream>
#include <list> 
#include <vector>


template <typename T>
concept HasBeginEnd = requires(T t) {
    t.begin() ;
    t.end();  
};

template <typename T>
concept IntergerOrString = std::integral<T> || std::is_same_v<T, std::string>;

template <typename T>
concept container = HasBeginEnd<T> && IntergerOrString<typename T::value_type>;

template <container T>
void isAccpetable(const T& c) {
    for (const auto& elem : c) {
        std::cout << elem << " ";
    }
}


int main(int argc, char** argv) {
    std::cout << "Hello, World!" << std::endl;
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<double> v2 = {1.2, 2, 3, 4, 5};
    isAccpetable(v1);
    return 0;
}