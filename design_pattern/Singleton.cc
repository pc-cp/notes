#include <iostream>
#include <string>

class Singleton {
    public:
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        static Singleton& getInstance() {
            static Singleton object;
            return object;
        }

        void setName(const std::string &name) {
            name_ = name;
        }

        const std::string& getName() {
            return name_;
        }


    private:
        Singleton() {

        };

        std::string name_;
};

int main() {
    Singleton& s1 = Singleton::getInstance();
    std::cout << &s1 << std::endl;
    s1.setName("s1");

    Singleton& s2 = Singleton::getInstance();
    std::cout << &s2 << std::endl;

    std::cout << s2.getName() << std::endl;
}