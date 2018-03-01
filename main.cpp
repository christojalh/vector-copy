#include <iostream>
#include "MyVector.h"

int main() {
    int data1[] = {1, 2, 3, 4, 5, 6};
    int data2[] = {5, 4, 3, 2, 1};
    int data3[] = {5, 4, 3, 2, 1, 0};
    int data4[] = {5, 4, 3, 2};


    MyVector<int> vec1(data1, 6);
    MyVector<int> vec2(data2, 5);
    MyVector<int> vec3(data3, 6);
    MyVector<int> vec4(data4, 4);

    std::cout << "vec1: ";
    vec1.printVec();
    std::cout << "vec2: ";
    vec2.printVec();

    // assign values to vector
    std::cout << "\nNow assigning 2s to vec1 using assign()\n";
    vec1.assign(10, 2);
    std::cout << "vec1: ";
    vec1.printVec();

    // assign value of one vector to another
    std::cout << "\nAssigning vec2 to vec1 using operator '='\n";
    vec1 = vec2;
    std::cout << "vec1: ";
    vec1.printVec();

    // at() throws an error if out of bounds
    // std::cout << vec1.at(10000);

    // front(), back()
    std::cout << "\nReturn first index using front()\n";
    std::cout << vec1.front();
    std::cout << "\nReturn last index using back()\n";
    std::cout << vec1.back();

    // push_back() appends an element 
    std::cout << "\nAppending an 8 to the vector\n";
    vec1.push_back( 8 );
    std::cout << "vec1: ";
    vec1.printVec();

    // pop_back removes the final element
    std::cout << "\nRemoving the last index with pop_back()\n";
    vec1.pop_back();
    std::cout << "vec1: ";
    vec1.printVec();

    // erase() removes an individual element
    std::cout << "\nRemoving the 2nd element with erase()\n";
    vec1.erase(1);
    std::cout << "vec1: ";
    vec1.printVec();

    // erase() can also remove a range of elements
    std::cout << "\nErasing range[1,3) with erase()\n";
    vec1.erase( 1, 3 );
    std::cout << "vec1: ";
    vec1.printVec();

    // capacity(), reserve(), shrink_to_fit()
    std::cout << "\nThe current capacity is: ";
    std::cout << vec1.capacity();

    std::cout << "\nReserving 10 extra capacity with reserve()";
    vec1.reserve(vec1.capacity() + 10);
    std::cout << "\nThe current capacity is: ";
    std::cout << vec1.capacity();

    std::cout << "\nvec1: ";
    vec1.printVec();
    std::cout << "Now removing unused capacity with shrink_to_fit()";
    vec1.shrink_to_fit();
    std::cout << "\nThe current capacity is: ";
    std::cout << vec1.capacity();

    // insert()
    std::cout << "\n\ninsert()ing 4s at position 1 with insert()\n";
    vec1.insert( 1, 4, 4 );
    std::cout << "vec1: ";
    vec1.printVec();

    // resize()
    std::cout << "\nShrinking vector to 3 elements with resize()\n";
    vec1.resize(3);
    std::cout << "vec1: ";
    vec1.printVec();

    std::cout << "Now making vec1 size 10 with resize(). Assigning value 7 to new elements\n";
    vec1.resize( 10, 7 );
    std::cout << "vec1: ";
    vec1.printVec();

    // swap()
    std::cout << "\nBefore swapping: ";
    std::cout << "\nvec1: ";
    vec1.printVec();
    std::cout << "vec2: ";
    vec2.printVec();
    std::cout << "Now swapping vector values with swap()\n";
    vec1.swap(vec2);
    std::cout << "vec1: ";
    vec1.printVec();
    std::cout << "vec2: ";
    vec2.printVec();   

    // comparison operators
    std::cout << "\nComparing vectors\n";
    std::cout << "vec1: ";
    vec1.printVec();
    std::cout << "vec3: ";
    vec3.printVec();       
    std::cout << "vec4: ";
    vec4.printVec();

    std::cout << "\nvec1==vec1: " << (vec1==vec1);
    std::cout << "\nvec1!=vec1: " << (vec1!=vec1);
    std::cout << "\nvec1>=vec1: " << (vec1>=vec1);
    std::cout << "\nvec1>vec1: " << (vec1>vec1);
    std::cout << "\nvec1<=vec1: " << (vec1<=vec1);
    std::cout << "\nvec1<vec1: " << (vec1<vec1);

    std::cout << "\n\nvec1==vec3: " << (vec1==vec3);
    std::cout << "\nvec1!=vec3: " << (vec1!=vec3);
    std::cout << "\nvec1>=vec3: " << (vec1>=vec3);
    std::cout << "\nvec1>vec3: " << (vec1>vec3);
    std::cout << "\nvec1<=vec3: " << (vec1<=vec3);
    std::cout << "\nvec1<vec3: " << (vec1<vec3);

    std::cout << "\n\nvec1==vec4: " << (vec1==vec4);
    std::cout << "\nvec1!=vec4: " << (vec1!=vec4);
    std::cout << "\nvec1>=vec4: " << (vec1>=vec4);
    std::cout << "\nvec1>vec4: " << (vec1>vec4);
    std::cout << "\nvec1<=vec4: " << (vec1<=vec4);
    std::cout << "\nvec1<vec4: " << (vec1<vec4);

    // empty(), size()
    std::cout << "\n\nChecking if vec1 is empty(). 0 = false; 1 = true\n";
    std::cout << vec1.empty();
    std::cout << "\nCurrent size is: " << vec1.size();
    std::cout << "\nNow clear() the contents\n";
    vec1.clear();
    std::cout << "Current size is: " << vec1.size();
    std::cout << "\nChecking if vec1 is empty(). 0 = false; 1 = true\n";
    std::cout << vec1.empty();

    // max_size()
    std::cout << "\n\nThe max size of a MyVector<int> is: ";
    std::cout << vec1.max_size() << "\n";

    return 0;
}
