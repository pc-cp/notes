#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <thread>
namespace callback{
    template <typename InputIt, typename UnaryFunction>
    UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f) {
        for(; first != last; first++) {
            f(*first);
        }
        return f;
    }
}

class Foo {
    public:
        Foo() : val_(0) {

        }

        void f(int val) { 
            this->val_ += val; 
            std::cout << this << std::endl;
        }

        int val_;
};

int main() {
    Foo foo;        //栈上对象
    foo.f(5);
    std::cout << foo.val_ << std::endl;

    std::thread t1(&Foo::f, &foo, 5);   // foo 被共享
    t1.join();
    std::cout << foo.val_ << std::endl; 
}