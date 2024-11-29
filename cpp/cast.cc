#include <iostream>

using namespace std;

class Base {
public:
    virtual void foo() {
        cout << "virtual foo() in Base" << endl;
    }
};

class Derived : public Base {
public:
    void foo() override {
        cout << "void foo() in Derived" << endl; 
    }
};

void testDynamicCast(Base* bp) {
    if (Derived *dp = dynamic_cast<Derived*>(bp)) {
        // use the Derived object to which dp points
        cout << "Derived" << endl;
    }
    else {  // bp points at a Base object
        // use the Base object to which bp points
        cout << "Base" << endl;
    }
}


int main() {
    // double d1 = 100.0;
    // int i1 = static_cast<int>(d1);

    // void *pd1 = &d1;     // ok: addredd of any nonconst object can be stored in a void*
    // // ok: convert void* back to the original pointer type
    // double *dp1 = static_cast<double *>(pd1);
    // printf("%f\n", *dp1);   // 100.000000

    // printf("----------------------------------------------\n");
    // /*const */char ch1 = 'a';
    // const char* pc = &ch1;
    // char *p1 = const_cast<char*>(pc);   // ok: but writing through p1 is UB
    // *p1 = 'b';
    // printf("%c\n", ch1);    // 'b'
    // // if ch1 is const char, then ch1 is not change. 'a' -> UB


    // printf("----------------------------------------------\n");
    // int i2 = 0x12345678;
    // // error: invalid static_cast from type 'int*' to type 'char*'
    // // char *pch1 = static_cast<char *>(&i2);

    // char *pch1 = reinterpret_cast<char *>(&i2);
    // for(int i = 0; i < 4; ++i) {
    //     printf("%x ", *(pch1+i));
    // }
    
    // string str(pch1);
    // printf("%s\n", str.c_str());

    // printf("----------------------------------------------\n");

    // Base b1;
    // Derived *pd1 = &b1;     // error: can't convert base to derived
    // Derived &rd1 = b1;      // error: can't convert base to derived
    Derived de1;
    Base *pb1 = &de1;       // ok: dynamic type is Derived
    // Derived *pd1 = pb1;     // error: can't convert base to derived
    testDynamicCast(pb1);
    Base b1;
    pb1 = &b1;
    testDynamicCast(pb1);
    // Derived *pde1 = dynamic_cast<Derived*>(pb1);
    // if we know pb1 is point Derived'object, we can cast in compile time.
    // Derived *pde1 = static_cast<Derived*>(pb1);  // ok
    // pde1->foo();
}