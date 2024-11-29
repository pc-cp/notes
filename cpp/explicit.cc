#include <iostream>

using namespace std;

class Foo {
    friend void swap(Foo& lhs, Foo& rhs);
public:
    Foo(int val) : val_(val) {
        cout << "Foo(int val)" << endl;
    }

    Foo(const Foo& rhs) : val_(rhs.val_) {
        cout << "Foo(const Foo& rhs)" << endl;
    }

    Foo(Foo&& rhs): val_(rhs.val_) {
        cout << "Foo(Foo&& rhs)" << endl;
        rhs.val_ = 0;
    }

    Foo& operator=(Foo foo) {
        swap(*this, foo);
        cout << "Foo& operator=(Foo foo)" << endl;
        return *this;
    }
    
private:
    int val_;
};

inline void swap(Foo& lhs, Foo& rhs) {
    using std::swap;
    swap(lhs.val_, rhs.val_);
}

int main() {
    Foo foo = 10;
}