#include <iostream>
#include <list> 
#include <vector>
#include <ranges>
#include <algorithm> 
#include <string>

// auto first_n_evens(std::size_t n) {
//     return std::views::iota(2) 
//            | std::views::transform([](int x) { return x * 2; })
//            | std::views::take(n);
// }


struct Book
{
    std::string title;
    int year;
    int pages;
    bool available;
};

bool after_2000(const Book& book) {
    return book.year > 2000;
}


int main(int argc, char** argv) {
    // std::vector<int> v1 = {1, 2, 3, 4, 5};
    // auto doubled = v1 | std::views::transform([](int i) { return i * 2; });
    
    // for (int i : doubled) {
    //     std::cout << i << " ";
    // }

    // std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // auto view = v2 | std::views::filter([](int x) { return x % 2 == 0; })
    //                | std::views::transform([](int x) { return x * x; })
    //                | std::views::take(3);

    // for (int x : view) {
    //     std::cout << x << " ";  
    // }
    // for (int x : first_n_evens(10)) {
    //     std::cout << x << " ";  
    // }

    std::vector<Book> books = {
        {"The C++ Programming Language", 2013, 1368, true},
        {"Clean Code", 2008, 464, true},
        {"The Alchemist", 1988, 208, true},
        {"Modern C++ Design", 2001, 352, false},
        {"Atomic Habits", 2018, 256, true},
        {"The Midnight Library", 2020, 288, true},
        {"Coraline", 2002, 192, true},
        {"The Road", 2006, 287, true},
        {"Educated", 2018, 334, true},
        {"Life of Pi", 2001, 224, false},
        {"Room", 2010, 296, true}
    };

    auto filtered_books = books | std::views::filter(after_2000)
    | std::views::filter([](const Book& book) { return book.pages < 300; });
    

    std::vector<std::string> titles;
    for (const auto& book : filtered_books) {
        titles.push_back(book.title);
    }

    std::ranges::sort(titles);
    
    auto selected_books = titles | std::views::take(3);


    for (const auto& t : selected_books) {
        std::cout << t << std::endl;
    }

    std::cout << std::endl;
    std::cout << "End Game" << std::endl;

    return 0;
}