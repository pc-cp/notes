#include <iostream>

using namespace std;

class Foo {
public:
    Foo() {

    }

    virtual void f();

    void g();

private:
    char ch_;
    int val_;
};

int main() {
    Foo foo;
    printf("%ld\n", sizeof(foo));
}