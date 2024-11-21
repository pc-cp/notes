#include <iostream>
#include <unordered_set>
#include <set>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
// 自定义的key类型
struct S {
    std::string first_name;
    std::string second_name;
};

// 自定义key类型时，两个要求(unordered_map通用)

// 自定义operator==
bool operator==(const S& lhs, const S& rhs) {
    return lhs.first_name == rhs.first_name
        && lhs.second_name == rhs.second_name;
}

// 自定义key的hash仿函数类

// 仿函数类，其实例化的对象是仿函数
template<>
struct std::hash<S> {
    std::size_t operator()(const S& s) const noexcept {
        std::size_t h1 = std::hash<std::string>{}(s.first_name);
        std::size_t h2 = std::hash<std::string>{}(s.second_name);

        return h1 ^ (h2 << 1);
    }
};

// -----------------------------------------------------------------------

// 像set、sort等需要重载小于号的，下面两种方法都可行，不过更建议第二种方法


// template<>
// struct std::less<S> {
//     bool operator()(const S& lhs, const S& rhs) const {
//         if(lhs.first_name != rhs.first_name) {
//             return lhs.first_name < rhs.first_name;
//         }
//         return lhs.second_name < rhs.second_name;
//     }
// };

bool operator<(const S& lhs, const S& rhs) {
    if(lhs.first_name != rhs.first_name) {
        return lhs.first_name < rhs.first_name;
    }
    return lhs.second_name < rhs.second_name;
}

int main() {
    std::unordered_set<S> names = {{"A1", "A2"}, {"B1", "B2"}, {"C1", "C2"}};

    for(auto const &s : names) {
        std::cout << s.first_name << ' ' << s.second_name << std::endl;
    }

    std::set<S> names2 = {{"A1", "A2"}, {"B1", "B2"}, {"C1", "C2"}};

    for(auto const &s : names2) {
        std::cout << s.first_name << ' ' << s.second_name << std::endl;
    }

    std::vector<S> vec = {{"B1", "B2"}, {"C1", "C2"}, {"A1", "A2"}};
    // std::sort(vec.begin(), vec.end(), std::less<S>{}); // 这个需要仿函数，而不仅仅是类型 OK
    std::sort(vec.begin(), vec.end()); // 这个需要仿函数，而不仅仅是类型    OK
    for(auto const &s : vec) {
        std::cout << s.first_name << ' ' << s.second_name << std::endl;
    }

    // 对于优先队列，也仅仅需要重载operator< 即可～～
    std::priority_queue<S> pq;
    for(auto const &s : names) {
        pq.push(s);
    }

    while(pq.size()) {
        auto s = pq.top();
        std::cout << s.first_name << ' ' << s.second_name << std::endl;
        pq.pop();
    }

}
