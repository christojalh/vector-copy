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

// Test: Supports large number of instances
// Expected: Prints range [0,large number]
template <typename T>
void instCap( MyVector<T> &vec ) {
    std::cout << "Verifying the vector's ability to store many instances of the vector\n";
    int largenumber = 10000;
    int count = 0;
    MyVector<int>::Iterator it = vec.begin();
    std::cout << "Starting instance: " << vec.getCurrentInst();
    std::cout << "\nCapacity: " << vec.getInstCapacity() << "\n";
    std::cout << "\nMaking " << largenumber << " instances...\n";
    while (count <= largenumber) {
        vec.insert(2, 1, 5);
        it = vec.begin();
        ++count;
    }
    std::cout << "\nEnd instance: " << vec.getCurrentInst();
    std::cout << "\nCapacity: " << vec.getInstCapacity() << "\n";
}

// Test: Invalidation after reallocation
// Expected: Iteration does not start
template <typename T>
void swapInvalidate( MyVector<T> &vec1, MyVector<T> &vec2 ) {
    std::cout << "\nVerifying invalidation after a swap of vectors\n\n";
    MyVector<int>::Iterator start = vec1.begin();
    MyVector<int>::Iterator end = vec1.end();
    vec1 = vec2; 
    ++start; 
    for (MyVector<int>::Iterator ii = vec1.begin(); ii != vec1.end(); ++ii)
    {
        std::cout << *ii << " ";
    }  
}

// Test: Keep old iterators valid if no reallocation occurs
// Expected: Print first element five times
template <typename T>
void keepValid( MyVector<T> &vec1 ) {
    std::cout << "Verifying the vector's ability to maintain valid Iterators of several instances\n";
    vec1.resize(20);
    MyVector<int>::Iterator start1 = vec1.begin();
    vec1.insert(2, 1, 2);
    MyVector<int>::Iterator start2 = vec1.begin();
    vec1.insert(2, 1, 2); // copy
    MyVector<int>::Iterator start3 = vec1.begin(); // copy
    vec1.insert(2, 1, 2); // copy
    MyVector<int>::Iterator start4 = vec1.begin(); // copy
    vec1.insert(2, 1, 2); // copy
    MyVector<int>::Iterator start5 = vec1.begin(); // copy

    std::cout << "\nIter 1 valid? " << start1.isValid() << " instance: " << start1.inst();
    std::cout << "\nIter 2 valid? " << start2.isValid() << " instance: " << start2.inst();
    std::cout << "\nIter 3 valid? " << start3.isValid() << " instance: " << start3.inst();
    std::cout << "\nIter 4 valid? " << start4.isValid() << " instance: " << start4.inst();
    std::cout << "\nIter 5 valid? " << start5.isValid() << " instance: " << start5.inst() << "\n";
}


// Test: Erase index and return the first invalid index
// Expected: returns pos + 1, because the first invalid is end() + 1
template <typename T>
void eraseInvalidate( MyVector<T> &vec1, int pos ) {
    MyVector<int>::Iterator start = vec1.begin();
    vec1.erase(pos);
    int count = 0;
    while (true) {
        if (!start.isValid()) {
            std::cout << "The first invalid index is " << count << "\n";
            return;
        }
        ++count;
        ++start;
    }

}

// Test iterators along with erase() for large numbers
template <typename T>
void bigErase( MyVector<T> &vec1 ) {
    vec1.clear();
    for (int ii = 0; ii < 200; ++ii) {
        vec1.push_back(ii);
    }

    std::cout << "\nIterating forwards\n";
    int count = 1;
    for (MyVector<int>::Iterator i = vec1.begin(); i != vec1.end(); ++i)
    {
        std::cout << *i << " ";
        if (count % 10 == 0) {
            std::cout << "\n";
        }
        count++;
    }

    std::cout << "\nlength is: " << vec1.length(); 
    std::cout << "\ncapacity is: " << vec1.capacity(); 

    std::cout << "\n\nerasing range [5,200)";
    vec1.erase(5,200);
    std::cout << "\n\nafter erasing, length is: " << vec1.length();
    std::cout << "\nafter erasing, capacity is: " << vec1.capacity();
    
    std::cout << "\n\nIterating forwards\n";
    count = 1;
    for (MyVector<int>::Iterator i = vec1.begin(); i != vec1.end(); ++i)
    {
        std::cout << *i << " ";
        if (count % 10 == 0) {
            std::cout << "\n";
        }
        count++;
    }
    std::cout << "\n";

    count = 1;
    std::cout << "\nReverse iterating\n";
    for (MyVector<int>::ReverseIterator i = vec1.rbegin(); i != vec1.rend(); ++i)
    {
        std::cout << *i << " ";
        if (count % 10 == 0) {
            std::cout << "\n";
        }
        count++;
    }
    std::cout << "\n";
}

template <typename T>
void vecGenFunctions( MyVector<T> &vec1 , MyVector<T> &vec2, MyVector<T> &vec3, MyVector<T> &vec4) {
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
}

template <typename T>
void reset( MyVector<T> &vec1 ) {
    vec1.clear();
    for (int ii = 0; ii < 6; ++ii) {
        vec1.push_back(ii);
    }
    std::cout << "The vector has been reset to range (0,5)\n";
}


int main() {
    int data1[] = {0, 1, 2, 3, 4, 5};
    int data2[] = {5, 4, 3, 2, 1};
    int data3[] = {5, 4, 3, 2, 1, 0};
    int data4[] = {5, 4, 3, 2};

    MyVector<int> vec1(data1, 6);
    MyVector<int> vec2(data2, 5);
    MyVector<int> vec3(data3, 6);
    MyVector<int> vec4(data4, 4);

    // swapInvalidate(vec1, vec2); // this should abort 
    keepValid(vec1);

    instCap(vec1);

    eraseInvalidate(vec1, 3);

    bigErase(vec1);

    reset(vec1);
    // vecGenFunctions(vec1, vec2, vec3, vec4);

    return 0;
}
