## Concepts in C++20

### Exercice 01

Define a concept called HasBeginEnd that checks whether a type has begin() and end() member functions.<br>
Implement a templated function print_container that:<br>
Accepts only types satisfying HasBeginEnd.<br>
Iterates over the container and prints each element.<br>
Test your function with:<br>
A std::vector<int><br>
A std::list<std::string><br>
A custom class that does not have begin()/end() (to show concept rejection).<br>
Extend the concept to check if the container's elements are printable (i.e., support operator<<).<br>

### Exercice 02 (Ranges)


Create a container that represents books in a library (e.g., std::vector<Book>) with sample data.
Use std::ranges::views to build a lazy pipeline that:
Selects only books that are available.
Filters books published after the year 2000.
Limits the result to books with less than 300 pages.
Transforms the result to extract just the titles.
Sort the resulting titles alphabetically
Return the first 3 books
Print the resulting list of titles.


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
 


### Exercice 03 (corotine)

Create a simple coroutine that simulates downloading a file.
Coroutine download(std::string name);
 
Each time the coroutine is resumed, the download should advance by 10% and print its current progress.
Ex:
Download 1: 10%
Download 1: 20%...
Download 1: 100%
Download 1: completed
 
Note Use std::suspend_always{} to suspend the coroutine after each 10% increment.
 
Inside we should have 2 scenario for testing:
1. 1 file download
2. 2 file download, with cooperative scheduling




### Docs

https://en.cppreference.com/cpp/header/iterator
