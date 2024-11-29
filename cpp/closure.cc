#include <iostream>
#include <functional>

class MyClass {
public:
    void sayHello(int n) const {
        std::cout << "Hello, number: " << n << std::endl;
    }
};

int main() {
    MyClass obj;
    auto boundFunc = std::bind(&MyClass::sayHello, &obj, std::placeholders::_1);

    boundFunc(42);      // 调用绑定的成员函数

    int x = 10;
    auto closure = [x](int y){return x + y;};   // 闭包捕获了x
    std::cout << closure(100) << std::endl;

}