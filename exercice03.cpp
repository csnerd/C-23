#include <iostream>
#include <list> 
#include <vector>
#include <ranges>
#include <algorithm> 
#include <string>

#include <utility>

// struct Coroutine{
//     struct promise_type{
//         coroutine get_return_object() {
//             return coroutine{std::coroutine_handle<promise_type>::from_promise(*this)};
//         }
//         std::suspend_always initial_suspend() { return {}; }
//         std::suspend_always final_suspend() noexcept { return {}; }
//         void return_void() {}
//         void unhandled_exception() { exception = std::current_exception(); }
//     };
//     std::coroutine_handle<coroutine::promise_type> handle;

//     Coroutine(std::coroutine_handle<promise_type> h) : handle(h) {}

//     ~Coroutine() {
//         if (handle) handle.destroy();
//     }

// };


// struct Generator : Coroutine {
//     struct promise_type : Coroutine::promise_type {
//         int current_value;
//         std::suspend_always yield_value(int value) {
//             current_value = value;
//             return {};
//         }
//     };

//     Generator(std::coroutine_handle<promise_type> h) : Coroutine(h) {}

//     int next() {
//         handle.resume();
//         return handle.promise().current_value;
//     }
// };


#include <iostream>
#include <coroutine>
#include <concepts>
#include <exception>

/*

Coroutine object
      │
      │ owns
      ▼
coroutine_handle
      │
      │ points to
      ▼
Coroutine frame
 ┌───────────────────────────┐
 │ promise_type              │
 │ parameters                │
 │ local variables           │
 │ execution state           │
 └───────────────────────────┘
 */

// Sample of generator: https://en.cppreference.com/cpp/language/coroutines#co_yield
struct Coroutine {
    // Defines how the coroutine should behave
    // Coroutine execution state is tracked in its frame.
    // In some cases
    struct promise_type {
        std::exception_ptr exception_;

        // constructs the external coroutine object and connects it to the already-created frame.
        Coroutine get_return_object() {
            // Obtain the coroutine frame
            return Coroutine{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }
        // what happens before the coroutine body starts executing
        std::suspend_always initial_suspend() { return {}; }
        // what happens when the corutine body has finished executing
        // final_suspend = suspend_always
        //     - external wrapper owns frame
        //     - destructor calls handle.destroy()
        // final_suspend = suspend_never
        //     - coroutine normally self-destroys
        //     - returned fire-and-forget object usually has no handle
        //     - destructor does nothing
        std::suspend_always final_suspend() noexcept { return {}; }

        // Defines what happens when we yield values from the coroutine
        // std::suspend_always yield_value(From&& from){}

        // initial_suspend is called when we create the coroutine
        // final_suspend when the coroutine ends (co_return)
        
        // coroutine does not return a value
        // void return_value(T value) // for returning a value
        void return_void() {}
        // ignore unhandled exceptions but save it, we can access it later
        void unhandled_exception() {exception_ = std::current_exception();}
    };

    // Coroutine handler
    // Allows external access to the coroutine frame
    // It can check the promise to assess the state of coroutine
    // .resume; .done; .promise; .destroy
    std::coroutine_handle<promise_type> handle;

    Coroutine(std::coroutine_handle<promise_type> h) : handle(h) {}

    // Delete copy, implement move
    // for segmentation fault safety, we don't want to have multiple handles pointing to the same frame
    Coroutine(const Coroutine&) = delete;
    Coroutine& operator=(const Coroutine&) = delete;

    Coroutine(Coroutine&& other) noexcept : handle(std::exchange(other.handle, {})) {}

    Coroutine& operator=(Coroutine&& other) noexcept {
        if (this != &other) {
            if (handle) handle.destroy();
            handle = std::exchange(other.handle, {});
        }
        return *this;
    }

    ~Coroutine() {
        // when final_suspend is suspend_always
        if (handle) handle.destroy();
        // = default
    }

    // Custom, we can define any accessing mechanism here
    bool resume() {
        if (!handle || handle.done()) { return false; }
        handle.resume();
        return !handle.done();
    }
};

Coroutine download(std::string url) {
    std::cout << "Downloading from: " << url << std::endl;

    for(int percent = 10; percent <= 100; percent += 10) {
        std::cout << "Downloaded : -->" << url << " : " << percent << "%" << std::endl;
        co_await std::suspend_always{};
    }
    std::cout << "Process done!" << std::endl;
    co_return;
}


void download_two_files() {

    std::vector<Coroutine> download_coroutines;

    download_coroutines.push_back(download("http://example.com/file1"));
    download_coroutines.push_back(download("http://example.com/file2"));

    bool any_running = true;
    while(download_coroutines.empty() == false && any_running) {
        any_running = false;
        for(auto& coro : download_coroutines) {
            if(coro.resume()) {
                any_running = true;
            }
        }
    }
    std::cout << "Download complete!" << std::endl;
}
int main() {
   std::cout << "Main: Creating coroutine\n";
   download_two_files();
//    /*
//     coroutine frame created
//       ↓
//     promise created inside frame
//         ↓
//     get_return_object()
//         ↓
//     create handle from promise
//         ↓
//     construct Coroutine{handle}
//         ↓
//     caller receives the control object*/
//    Coroutine coro = download("http://example.com");
//    std::cout << "Main: Resuming coroutine (1)\n";
//    coro.resume();
//    std::cout << "Main: Resuming coroutine (2)\n";
//    coro.resume();
//    std::cout << "Main: Resuming coroutine (3)\n";
//    coro.resume();
//    std::cout << "Main: Coroutine finished\n";
//    return 0;
}



// int main(int argc, char** argv) {
    

//     std::cout << std::endl;
//     std::cout << "End Game" << std::endl;

//     return 0;
// }