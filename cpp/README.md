## callback.cc
- 什么是成员函数: regular not-defined-in-any-class functions with an extra hidden parameter

## test_unordered_set.cc
- unordered_map/set 的key类型如果是自定义类型，需要重载operator== 和 std::hash<keyType>(这是一个仿函数类型)
- map/set 的key类型的话会容易很多，只需要std::less<keyType>(这也是一个仿函数)
- sort的话，如果是自定义类型或者自定义比较操作，可以提供仿函数对象: std::less<keyType>{}。

## closure.cc
- Closure(闭包)是一个CS术语，通常指一种包含函数和与其相关的环境（或状态）的组合。简单来说，闭包不仅包含函数的定义，还"捕获"了创建它时的上下文，使得它可以在不同的作用域中使用这些捕获的变量。
- cpp中常见闭包: std::bind 或 lambda表达式
作用
- 延续上下文: 运行函数在离开定义它的作用域后, 仍能访问捕获的变量。
- 实现回调、延迟调用和事件驱动逻辑。
- 减少样板代码: 直接将状态与逻辑封装在一起。

## Named Casts(Avoid casts)
- **Casts interfere with normal type checking.**
- static_cast:
  - Any well-defined type conversion, other than those involving **low-level const**, can be requested using a static_cast.
  - The cast informs both the reader of the program and the compiler that we are aware of and not concerned about the potential loss of precision.
  - A static_cast is also useful to perform a conversion that the compiler will not generate automatically. For example, we can use a static_cast to retrive a pointer value that was stored in a void* pointer
  ```cpp
    double d1 = 100.0;
    int i1 = static_cast<int>(d1);

    void *pd1 = &d1;     // ok: addredd of any nonconst object can be stored in a void*
    // ok: convert void* back to the original pointer type
    double *dp1 = static_cast<double *>(pd1);
    printf("%f\n", *dp1);   // 100.000000
  ```

- const_cast
  - A const_cast changes only a low-level const in its operand.
  - Conventionally we say that a cast that converts a const object to a nonconst type "cast away the const." Once we have cast away the const of an object, the compiler will no longer prevent us from writing to that object. If the object was originally not a const, using a cast to obtain write access is legal. However, **using a const_cast in order to write to a const object is undefined**.
  ```cpp
  /*const */char ch1 = 'a';
    const char* pc = &ch1;
    char *p1 = const_cast<char*>(pc);   // ok: but writing through p1 is UB if ch1 is *const char*
    *p1 = 'b';
    printf("%c\n", ch1);    // 'b'
    // if ch1 is const char, then ch1 is not change. 'a' -> UB
  ```
  - A const_cast is most useful in the context of overloaded functions: ? 

- reinterpret_cast
  - A reinterpret_cast generally performs a low-level reinterpretation of the bit pattern of its operands. As an example, given the following cast:
  ```cpp
    int i2 = 0x12345678;
    // error: invalid static_cast from type 'int*' to type 'char*'
    // char *pch1 = static_cast<char *>(&i2);

    char *pch1 = reinterpret_cast<char *>(&i2);
    for(int i = 0; i < 4; ++i) {
        printf("%x ", *(pch1+i));
    }
    
    // absolutely correct - albeit meaningless or worse!
    string str(pch1);       // dangerous, is likely to result in bizarre run-time behavior
    
    printf("%s\n", str.c_str());
  ```
  - we must never forget that the actual addressed by pch1 is an int, not a char. Any use of pch1 that assumes **it's an ordinary char* is likely to fail at run time**.
- dynamic_cast
  - Because a **base object might or might not be part of a derived object**, there is no automatic conversion from the base clas to its derived class:
    ```cpp
    Base b1;
    Derived *pd1 = &b1;     // error: can't convert base to derived
    Derived &rd1 = b1;      // error: can't convert base to derived
    ```
  - If these assignments were legal, we might attempt to use `pd1` or `rd1` to use members that do not exist in `b1`. 
  - What is sometimes a bit surprising is that **we can't convert from base to derived even when a base pointer or reference is bound to a derived object**:
    ```cpp
    Derived de1;
    Base *pb1 = &de1;       // ok: dynamic type is Derived
    Derived *pd1 = pb1;     // error: can't convert base to derived
    ```
  - The compiler has no way to know (at compile time) that a specific conversion will be safe at run time. *The compiler looks only at the static types of the pointer or reference to determine whether a conversion is legal.* If the base class has one or more virtual functions, we can use a `dynamic_cast` to **request a conversion that is checked at run time**. Alternatively, in those cases when we know that the conversion from base to derived is safe, we can use a `static_cast` to override the compiler.
    ```cpp
    Derived de1;
    Base *pb1 = &de1;       // ok: dynamic type is Derived
    // Derived *pd1 = pb1;     // error: can't convert base to derived

    Derived *pde1 = dynamic_cast<Derived*>(pb1);
    // if we know pb1 is point Derived'object, we can cast in compile time.
    // Derived *pde1 = static_cast<Derived*>(pb1);  // ok
    ```
  - If a `dynamic_cast` to a pointer type fails, the result is `0`. If a `dynamic_cast` to a reference type fails, the operator throws an exception of type `bad_cast`.
    ```cpp
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
    Derived de1;
    Base *pb1 = &de1;       // ok: dynamic type is Derived
    // Derived *pd1 = pb1;     // error: can't convert base to derived
    testDynamicCast(pb1);
    Base b1;
    pb1 = &b1;
    testDynamicCast(pb1);

    /*
    Derived
    Base
    */
    ```
## const.cc
- top-level const has no effect on the objects that can be passed to the function. A parameter that has a top-level const is indistinguishable from one without a top-level const:
    ```cpp
    void f(int i) {
        cout << "void f(int i)" << endl;
    }

    // redefinition of ‘void f(int)’
    void f(const int i) {
        cout << "void f(const int i)" << endl;
    }
    ```
- We can overload based on whether the parameter is a reference(or pointer) to the const or nonconst version of a given type; **such constS are low-level**:
    ```cpp
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
    ```
- Because there is no conversion from const, we can pass a const object (or a pointer to const) only to the version with a const parameter. Because there is a conversion to const, we can call **either function on a nonconst object or a pointer to nonconst**. However, (chap6.6.1), the compiler will prefer the nonconst versions when we pass a nonconst object or pointer to nonconst.

## poly.cc
- 构造函数为什么不能是虚函数？
  - 虚函数的调用依赖于对象中的虚指针指向的虚函数表，而虚指针的初始化发生在构造函数执行期间。如果构造函数本身是虚函数，就需要依赖尚未初始化的虚指针，导致无法正确调用构造函数，进而无法完成对象的实例化。