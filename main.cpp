#include <iostream>
#include "MyVector.h"

int main() {
    char data1[] = {'a','p','p','l','e'};
    char data2[] = {'p','i','e'};


    MyVector<char> vec1(data1, 5);
    MyVector<char> vec2(data2, 3);
    vec1.printVec();
    vec2.printVec();


    // std::cout << "The length is: " << vec2.length() << "\n";
    // std::cout << "The capacity is: " << vec2.capacity() << "\n";
    return 0;
}
