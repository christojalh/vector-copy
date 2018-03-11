#include <iostream>
#ifndef MYVECTOR_HEADER
#define MYVECTOR_HEADER

template<typename T>
class MyVector
{

// declare inner Iterator classes 
public:
    class Iterator
    {
    public:
        // Constructor + Destructor
        Iterator(T* index, MyVector<T>* vec);
        ~Iterator();

        // Operators
        Iterator& operator++();
        Iterator& operator--();
        bool operator==( const Iterator& rhs);
        bool operator!=( const Iterator& rhs);
        T& operator*();
        // Other operators are disabled
        void operator>( const Iterator& rhs);
        void operator>=( const Iterator& rhs);
        void operator<=( const Iterator& rhs);
        void operator<( const Iterator& rhs);
        void operator*( const Iterator& rhs);
        void operator+( const Iterator& rhs);
        void operator-( const Iterator& rhs);

        // Access functions
        int inst();
        const int inst() const;
        T* index(); 
        const T* index() const; 

        // Check validity
        const bool isValid() const;

    private:
        T* m_index;
        int m_inst; // instance
        MyVector<T>* parent; 
    };

    class ReverseIterator
    {
    public:
        // Constructor + Destructor
        ReverseIterator(T* index, MyVector<T>* vec);
        ~ReverseIterator();

        // Operators
        ReverseIterator& operator++();
        ReverseIterator& operator--();
        bool operator==( const ReverseIterator& rhs);
        bool operator!=( const ReverseIterator& rhs);
        T& operator*();
        // other operators are disabled
        void operator>( const ReverseIterator& rhs);
        void operator>=( const ReverseIterator& rhs);
        void operator<=( const ReverseIterator& rhs);
        void operator<( const ReverseIterator& rhs);
        void operator*( const ReverseIterator& rhs);
        void operator+( const ReverseIterator& rhs);
        void operator-( const ReverseIterator& rhs);

        // Access functions
        int inst();
        const int inst() const;
        T* index(); 
        const T* index() const; 

        // Check validity
        const bool isValid() const;

    private:
        T* m_index;
        int m_inst; // instance
        MyVector<T>* parent; 
    };

public:
    // Constructor + Destructor
    MyVector( T* input, int length );
    ~MyVector();

    // Member function
    void assign( int count, const T& value );

    // Operator Overloading
    MyVector& operator=( const MyVector& other );
    T& operator[]( int pos );
    const T& operator[]( int pos ) const;

    // Function Overloading
    T& at( int pos );
    const T& at( int pos ) const;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    const int length() const;

    // Capacity
    bool empty();
    const bool empty() const;

    int size();
    const int size() const;

    double max_size();
    const double max_size() const;

    void reserve( int newcap );

    int capacity();
    const int capacity() const;

    void shrink_to_fit();



    // Modifiers
    void clear();

    // inserts 'count' copies of value before index pos
    void insert( int pos, int count, const T& value );

    // deletes element at pos
    void erase( int pos );
    // deletes elements in range [first:last)
    void erase( int first, int last);

    // appends element to end of container
    void push_back( const T& value );

    // removes last element of container
    void pop_back(); 

    void resize( int count );
    void resize( int count, const T& value );

    void swap( MyVector& other );

    // Operators
    bool operator==( const MyVector& rhs);
    bool operator!=( const MyVector& rhs);
    bool operator<(  const MyVector& rhs);
    bool operator<=( const MyVector& rhs);
    bool operator>( const MyVector& rhs);
    bool operator>=( const MyVector& rhs);

    // Misc/Personal
    void printVec();

    void incCapacity();
    void decCapacity();
    bool isQuarterEmpty();

    // Iterators
    bool isValid( Iterator it );
    void updInvalid();
    void incInstCapacity();
    int getInstCapacity();
    int getCurrentInst();
    Iterator begin();
    Iterator end();
    ReverseIterator rbegin();
    ReverseIterator rend();

private:
    T* m_data;
    int m_length; // number of elements
    int m_trueSize; // capacity of array
    friend class Iterator;


    // Rules regarding the data in m_instanceChecker
    //  1) if m_data is deleted, a new instance is created
    //      upon the declaration of a new iterator and all 
    //      previous instances are immediately invalidated
    //  2) if an index is deleted or inserted, that index
    //      is stored in m_instanceChecker. Indices > that
    //      index are declared invalid. An array starts 
    //      with the first element to the last element + 1
    //      being valid. 
    //  Note: This array implements automatic resizing methods
    T** m_instChecker; // validates Iterators
    int m_instCapacity;

    // Incremented each time an iterator is declared while
    // m_createNewInstance is true
    int m_currentInst;

    // Set to true after length() or capacity() are changed
    // Set to false only after a new iterator is declared.
    // This way, you can create multiple Iterators 
    // without incrementing the instance if m_data 
    // doesn't change, because it will remain false until
    // a change is made. 
    bool m_createNewInst;

    // For large numbers of instances, having a firstValidInstance
    // allows us to skip over "legacy" instances when 
    // validating an iterator
    int m_firstValidInst;


};

// template<typename T>
// std::ostream& operator<< (std::ostream& os, const MyVector<T>& vec);

#endif