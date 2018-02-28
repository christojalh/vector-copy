template<typename T>
class MyVector
{
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

private:
    T* m_data;
    int m_length; // number of elements
    int m_trueSize; // capacity of array
};