#include <iostream>
#include "MyVector.h"

// template<typename T>
// std::ostream& operator<< (std::ostream& os, const MyVector<T>& vec) {
//     for (int ii = 0; ii < vec.length(); ++ii) {
//         os << vec[ii] << " ";
//     }
//     os << "\n";

//     return os;
// }

int main() {
    int data1[] = {0, 1, 2, 3, 4, 5};
    int data2[] = {5, 4, 3, 2, 1};
    int data3[] = {5, 4, 3, 2, 1, 0};
    int data4[] = {5, 4, 3, 2};

    MyVector<int> vec1(data1, 6);
    MyVector<int> vec2(data2, 5);
    MyVector<int> vec3(data3, 6);
    MyVector<int> vec4(data4, 4);


    // std::cout << vec1;

    // // Test: Supports large number of instances
    // // Expected: Prints range [0,large number]
    // int largenumber = 10000;
    // int count = 0;
    // MyVector<int>::Iterator it = vec1.begin();
    // std::cout << "Starting instance: " << vec1.getCurrentInst();
    // std::cout << "\nCapacity of instChecker: " << vec1.getInstCapacity();
    // while (count <= largenumber) {
    //     vec1.insert(2, 1, 5);
    //     it = vec1.begin();
    //     ++count;
    // }
    // std::cout << "\nEnd instance: " << vec1.getCurrentInst();
    // std::cout << "\nCapacity of instChecker: " << vec1.getInstCapacity();

    // // Test: Invalidation of iterator after insert/delete
    // // Expected: Stops at changed index
    // vec1.resize(20);
    // MyVector<int>::Iterator start = vec1.begin();
    // MyVector<int>::Iterator end = vec1.end();
    // while (start != end) {
    //     if ((*start) == vec1[3]) {
    //         vec1.erase(3);
    //     }
    //     std::cout << *start << " ";
    //     ++start;
    // }       

    // // Test: Invalidation after reallocation
    // // Expected: Iteration does not start
    // MyVector<int>::Iterator start = vec1.begin();
    // MyVector<int>::Iterator end = vec1.end();
    // vec1 = vec2; 
    // ++start; 
    // for (MyVector<int>::Iterator ii = vec1.begin(); ii != vec1.end(); ++ii)
    // {
    //     std::cout << *ii << " ";
    // }   

    // // Test: Keep old iterators valid if no reallocation occurs
    // // Expected: Print first 2 elements three times then abort
    // MyVector<int>::Iterator start1 = vec1.begin();
    // MyVector<int>::Iterator start2 = vec1.begin(); // copy
    // MyVector<int>::Iterator start3 = vec1.begin(); // copy
    // while ((*start1) != vec1[5]) {
    //     vec1.erase(2);
    //     while ((*start2) != vec1[2]) {
    //         std::cout << *start2 << " ";
    //         ++start2;
    //     }
    //     while ((*start3) != vec1[2]) {
    //         std::cout << *start3 << " ";
    //         ++start3;
    //     }
    //     std::cout << *start1 << " ";
    //     ++start1;
    // }

    // // Test: Same as above, but for R_Iterators
    // // Expected: Print first 2 elements in reverse three times. Does
    // //              not abort
    // MyVector<int>::ReverseIterator start1 = vec1.rbegin();
    // MyVector<int>::ReverseIterator start2 = vec1.rbegin(); // copy
    // MyVector<int>::ReverseIterator start3 = vec1.rbegin(); // copy

    // MyVector<int>::ReverseIterator end = vec1.rend(); // copy

    // ++start1; ++start1; ++start1; ++start1; 
    // ++start2; ++start2; ++start2; ++start2;    
    // ++start3; ++start3; ++start3; ++start3;   
    // while (start1 != end) {
    //     // vec1.erase(3);
    //     while (start2 != end) {
    //         std::cout << *start2 << " ";
    //         ++start2;
    //     }
    //     while (start3 != end) {
    //         std::cout << *start3 << " ";
    //         ++start3;
    //     }
    //     std::cout << *start1 << " ";
    //     ++start1;
    // }

    // // Test: Creates new instance after changing an index
    // // Expected: full iteration through vector 
    // std::cout << "Erasing vec1[3]\n";
    // vec1.erase(3);
    // for (MyVector<int>::Iterator ii = vec1.begin(); ii != vec1.end(); ++ii)
    // {
    //     std::cout << *ii << " ";
    // }    
    // std::cout << "\nInserting some 10s\n";
    // vec1.insert(2, 5, 10);
    // for (MyVector<int>::Iterator ii = vec1.begin(); ii != vec1.end(); ++ii)
    // {
    //     std::cout << *ii << " ";
    // }    

    // // Test: Concurrent and independent iteration by multiple iterators
    // for (MyVector<int>::Iterator ii = vec1.begin(); ii != vec1.end(); ++ii)
    // {
    //     for (MyVector<int>::Iterator jj = vec1.begin(); jj != vec1.end(); ++jj)
    //     {
    //         std::cout << *ii << *jj << " ";
    //     }
    //     std::cout << "\n";
    // }

    // // Test iterators along with erase() for large numbers
    // vec1.clear();
    // for (int ii = 0; ii < 200; ++ii) {
    //     vec1.push_back(ii);
    // }

    // std::cout << "\nIterating forwards\n";
    // int count = 1;
    // for (MyVector<int>::Iterator i = vec1.begin(); i != vec1.end(); ++i)
    // {
    //     std::cout << *i << " ";
    //     if (count % 10 == 0) {
    //         std::cout << "\n";
    //     }
    //     count++;
    // }

    // std::cout << "\nlength is: " << vec1.length(); 
    // std::cout << "\ncapacity is: " << vec1.capacity(); 

    // std::cout << "\n\nerasing range [5,200)";
    // vec1.erase(5,200);
    // std::cout << "\n\nafter erasing, length is: " << vec1.length();
    // std::cout << "\nafter erasing, capacity is: " << vec1.capacity();
    
    // std::cout << "\n\nIterating forwards\n";
    // count = 1;
    // for (MyVector<int>::Iterator i = vec1.begin(); i != vec1.end(); ++i)
    // {
    //     std::cout << *i << " ";
    //     if (count % 10 == 0) {
    //         std::cout << "\n";
    //     }
    //     count++;
    // }
    // std::cout << "\n";

    // count = 1;
    // std::cout << "\nReverse iterating\n";
    // for (MyVector<int>::ReverseIterator i = vec1.rbegin(); i != vec1.rend(); ++i)
    // {
    //     std::cout << *i << " ";
    //     if (count % 10 == 0) {
    //         std::cout << "\n";
    //     }
    //     count++;
    // }
    // std::cout << "\n";



    // // START general function tests
    // std::cout << "vec1: ";
    // vec1.printVec();
    // std::cout << "vec2: ";
    // vec2.printVec();

    // // assign values to vector
    // std::cout << "\nNow assigning 2s to vec1 using assign()\n";
    // vec1.assign(10, 2);
    // std::cout << "vec1: ";
    // vec1.printVec();

    // // assign value of one vector to another
    // std::cout << "\nAssigning vec2 to vec1 using operator '='\n";
    // vec1 = vec2;
    // std::cout << "vec1: ";
    // vec1.printVec();

    // // at() throws an error if out of bounds
    // // std::cout << vec1.at(10000);

    // // front(), back()
    // std::cout << "\nReturn first index using front()\n";
    // std::cout << vec1.front();
    // std::cout << "\nReturn last index using back()\n";
    // std::cout << vec1.back();

    // // push_back() appends an element 
    // std::cout << "\nAppending an 8 to the vector\n";
    // vec1.push_back( 8 );
    // std::cout << "vec1: ";
    // vec1.printVec();

    // // pop_back removes the final element
    // std::cout << "\nRemoving the last index with pop_back()\n";
    // vec1.pop_back();
    // std::cout << "vec1: ";
    // vec1.printVec();

    // // erase() removes an individual element
    // std::cout << "\nRemoving the 2nd element with erase()\n";
    // vec1.erase(1);
    // std::cout << "vec1: ";
    // vec1.printVec();

    // // erase() can also remove a range of elements
    // std::cout << "\nErasing range[1,3) with erase()\n";
    // vec1.erase( 1, 3 );
    // std::cout << "vec1: ";
    // vec1.printVec();

    // // capacity(), reserve(), shrink_to_fit()
    // std::cout << "\nThe current capacity is: ";
    // std::cout << vec1.capacity();

    // std::cout << "\nReserving 10 extra capacity with reserve()";
    // vec1.reserve(vec1.capacity() + 10);
    // std::cout << "\nThe current capacity is: ";
    // std::cout << vec1.capacity();

    // std::cout << "\nvec1: ";
    // vec1.printVec();
    // std::cout << "Now removing unused capacity with shrink_to_fit()";
    // vec1.shrink_to_fit();
    // std::cout << "\nThe current capacity is: ";
    // std::cout << vec1.capacity();

    // // insert()
    // std::cout << "\n\ninsert()ing 4s at position 1 with insert()\n";
    // vec1.insert( 1, 4, 4 );
    // std::cout << "vec1: ";
    // vec1.printVec();

    // // resize()
    // std::cout << "\nShrinking vector to 3 elements with resize()\n";
    // vec1.resize(3);
    // std::cout << "vec1: ";
    // vec1.printVec();

    // std::cout << "Now making vec1 size 10 with resize(). Assigning value 7 to new elements\n";
    // vec1.resize( 10, 7 );
    // std::cout << "vec1: ";
    // vec1.printVec();

    // // swap()
    // std::cout << "\nBefore swapping: ";
    // std::cout << "\nvec1: ";
    // vec1.printVec();
    // std::cout << "vec2: ";
    // vec2.printVec();
    // std::cout << "Now swapping vector values with swap()\n";
    // vec1.swap(vec2);
    // std::cout << "vec1: ";
    // vec1.printVec();
    // std::cout << "vec2: ";
    // vec2.printVec();   

    // // comparison operators
    // std::cout << "\nComparing vectors\n";
    // std::cout << "vec1: ";
    // vec1.printVec();
    // std::cout << "vec3: ";
    // vec3.printVec();       
    // std::cout << "vec4: ";
    // vec4.printVec();

    // std::cout << "\nvec1==vec1: " << (vec1==vec1);
    // std::cout << "\nvec1!=vec1: " << (vec1!=vec1);
    // std::cout << "\nvec1>=vec1: " << (vec1>=vec1);
    // std::cout << "\nvec1>vec1: " << (vec1>vec1);
    // std::cout << "\nvec1<=vec1: " << (vec1<=vec1);
    // std::cout << "\nvec1<vec1: " << (vec1<vec1);

    // std::cout << "\n\nvec1==vec3: " << (vec1==vec3);
    // std::cout << "\nvec1!=vec3: " << (vec1!=vec3);
    // std::cout << "\nvec1>=vec3: " << (vec1>=vec3);
    // std::cout << "\nvec1>vec3: " << (vec1>vec3);
    // std::cout << "\nvec1<=vec3: " << (vec1<=vec3);
    // std::cout << "\nvec1<vec3: " << (vec1<vec3);

    // std::cout << "\n\nvec1==vec4: " << (vec1==vec4);
    // std::cout << "\nvec1!=vec4: " << (vec1!=vec4);
    // std::cout << "\nvec1>=vec4: " << (vec1>=vec4);
    // std::cout << "\nvec1>vec4: " << (vec1>vec4);
    // std::cout << "\nvec1<=vec4: " << (vec1<=vec4);
    // std::cout << "\nvec1<vec4: " << (vec1<vec4);

    // // empty(), size()
    // std::cout << "\n\nChecking if vec1 is empty(). 0 = false; 1 = true\n";
    // std::cout << vec1.empty();
    // std::cout << "\nCurrent size is: " << vec1.size();
    // std::cout << "\nNow clear() the contents\n";
    // vec1.clear();
    // std::cout << "Current size is: " << vec1.size();
    // std::cout << "\nChecking if vec1 is empty(). 0 = false; 1 = true\n";
    // std::cout << vec1.empty();

    // // max_size()
    // std::cout << "\n\nThe max size of a MyVector<int> is: ";
    // std::cout << vec1.max_size() << "\n";

    return 0;
}
