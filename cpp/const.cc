#include <iostream>

using namespace std;

// void f(int i) {
//     cout << "void f(int i)" << endl;
// }

// // redefinition of ‘void f(int)’
// void f(const int i) {
//     cout << "void f(const int i)" << endl;
// }

// functions taking const and nonconst references or pointers have different parameters
// declarations for four independent, overloaded functions.
void f(int &ri) {
    cout << "void f(int &ri)" << endl;
}

void f(const int& cri) {
    cout << "void f(const int& cri)" << endl;
}

void f(int *pi) {
    cout << "void f(int *pi)" << endl;
}

void f(const int* cpi) {
    cout << "void f(const int* cpi)" << endl;
}

int main() {
    int i = 10;
    int *pi = &i;
    const int ci = 10;
    const int *cpi = &ci;

    
    f(i);
    f(pi);
    f(ci);
    f(cpi);

    /*
    void f(int &ri)
    void f(int *pi)
    void f(const int& cri)
    void f(const int* cpi)
    */
}