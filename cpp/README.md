## callback.cc
- 什么是成员函数: regular not-defined-in-any-class functions with an extra hidden parameter

## test_unordered_set.cc
- unordered_map/set 的key类型如果是自定义类型，需要重载operator== 和 std::hash<keyType>(这是一个仿函数类型)
- map/set 的key类型的话会容易很多，只需要std::less<keyType>(这也是一个仿函数)
- sort的话，如果是自定义类型或者自定义比较操作，可以提供仿函数对象: std::less<keyType>{}。