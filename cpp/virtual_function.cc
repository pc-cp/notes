#include <iostream>

class Component {
    public:
        Component() {
            std::cout << "Component ctor" << std::endl;
        }
        ~Component() {
            std::cout << "Component dtor" << std::endl;
        }
};

class Base {
    public:
        Base() {
            std::cout << "Base ctor" << std::endl;
        }

        virtual ~Base() {
            std::cout << "Base dtor" << std::endl;
        }

        virtual void func() {
            std::cout << "Base::func()" << std::endl;
        }

    private:
        Component com;
};

class Derived : public Base {
    public:
        Derived() : Base() {
            std::cout << "Derived ctor" << std::endl;
        }

        ~Derived() {
            std::cout << "Derived dtor" << std::endl;
        }

        void func() override {
            std::cout << "Derived::func()" << std::endl;
        }
    private:
        // Component com;
};

int main() {
    Derived d;
    Base *b = &d;
    b->func();
}