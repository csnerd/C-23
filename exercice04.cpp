#include <iostream>
#include <list> 
#include <vector>
#include <ranges>
#include <algorithm> 
#include <string>

#include <utility>
#include <algorithm>  
#include <cctype>  
#include <cstdlib>  
#include <iomanip>  
#include <iostream>  
#include <regex>  
#include <sstream>  
#include <iostream>  
#include <map>  
#include <sstream>  
#include <stdexcept>  
#include <string>  
#include <vector>  
#include <format>


#include <chrono>

using namespace std::chrono;

auto tz = locate_zone("Europe/Kiev");
zoned_time zt{tz, system_clock::now()};


#include <iostream>
#include <regex>
#include <chrono>

using namespace std;
using namespace std::chrono;

sys_days parseCommand(const string& cmd)
{
    auto today = floor<days>(system_clock::now());
    year_month_day ymd{today};
    smatch m;

    // Postpone by N months
    if (regex_match(cmd, m, regex(R"(Postpone by (\d+) months?)")))
        return sys_days{ymd + months(stoi(m[1]))};

    // Move to next Friday
    if (regex_match(cmd, regex(R"(Move to next Friday)")))
    {
        weekday wd{today};           // current weekday
        weekday target{5};           // Friday (Sun=0)
        auto diff = (target.c_encoding() - wd.c_encoding() + 7) % 7;
        if (diff == 0) diff = 7;
        return today + days(diff);
    }

    // First Monday of next month
    if (regex_match(cmd,
        regex(R"(Reschedule to the first Monday of next month)")))
    {
        auto first = ymd.year() / ymd.month() / 1 + months{1};

        sys_days d{first};
        while (weekday{d} != Monday)
            d += days{1};

        return d;
    }

    throw runtime_error("Unsupported command");
}

 
struct Task
{
    int id;
    std::string title;
    std::chrono::sys_days dueDate;
};


struct TaskManager {
    vector<Task> tasks;

    void addTask(int id, const std::string& title, const std::chrono::sys_days& dueDate) {
        tasks.push_back({id, title, dueDate});
    }
    void rescheduleTask(int id,std::string str) {
        auto newDate = parseCommand(str);
        auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task) {
            return task.id == id;
        });
        if (it != tasks.end()) {
            it->dueDate = newDate;
            it->title += " (Rescheduled: " + str + ")";
        }
    }

    void printTasks() const {
        for (const auto& task : tasks)
        {
            auto ymd = std::chrono::year_month_day{task.dueDate};

            std::cout
                << "Task ID: " << task.id
                << ", Title: " << task.title
                << ", Due Date: "
                << int(ymd.year()) << '-'
                << unsigned(ymd.month()) << '-'
                << unsigned(ymd.day())
                << '\n';
        }
    }
};
 


int main() {
    TaskManager manager;

    auto today = floor<days>(system_clock::now());

    manager.addTask(1, "first", today);
    manager.addTask(2, "secound", today );
    manager.addTask(3, "third", today );

    cout << "Initial Tasks:\n";
    manager.printTasks();

    manager.rescheduleTask(1, "Move to next Friday");
    manager.rescheduleTask(2, "Postpone by 2 months");
    manager.rescheduleTask(3, "Reschedule to the first Monday of next month");

    cout << "\nUpdated Tasks:\n";
    manager.printTasks();
   

    return 0;
}



