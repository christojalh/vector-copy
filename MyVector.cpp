/* Christopher Lee	   
 * February 26th, 2018
 * 
 * This program is a copy class of std::vector with reduced constructor functionality
 * To create a vector using this program, pass in an array of data and the length of the array
 * 
 * Functions included:
 * -Element access
 * -Capacity
 * -Modifiers
 * -Lexicographical compare operators (==, !=, >=, >, <=, <)
 * 
 * Example usage
 *  >> int data[] = {1, 2, 3};
 *  >> MyVector<int> sampleVec( data, 3 ); 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cmath>
#include "MyVector.h"

// START Member functions
// Constructor
template<typename T>
MyVector<T>::MyVector(T* input,int length) {
    m_length = length;
    m_trueSize = m_length;
    m_data = new T[m_length];
    memcpy(m_data, input, m_length * sizeof(T));
}

// Destructor
template<typename T>
MyVector<T>::~MyVector() {
    delete m_data;
}

// ***
template<typename T>
void MyVector<T>::assign(int count, const T& value) {
    T* temp = new T[count];
    for (int i = 0; i < count; ++i) {
        temp[i] = value;
    }
    delete m_data;
    m_data = temp; 
    m_length = count;
    m_trueSize = count;
}

// ***
template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    T* temp = new T[other.capacity()];
    memcpy(temp, other.m_data, other.length() * sizeof(T));
    delete m_data;
    m_data = temp;
    m_length = other.length();
    m_trueSize = other.capacity();
}


// START Element access
// ***
template<typename T>
T& MyVector<T>::operator[]( int pos ) {
    return m_data[pos];
};

// ***
template<typename T>
const T& MyVector<T>::operator[]( int pos ) const {
    return m_data[pos];
};

// *** 
template<typename T>
T& MyVector<T>::at( int pos ) {
    if (pos < 0 || pos >= length()) {
        throw std::out_of_range("Index out of bounds\n");
    }
    return m_data[pos];
};

// ***
template<typename T>
const T& MyVector<T>::at( int pos ) const {
    if (pos < 0 || pos >= length()) {
        throw std::out_of_range("Index out of bounds\n");
    }
    return m_data[pos];
};

template<typename T>
T& MyVector<T>::front() {
    return m_data[0];
};

template<typename T>
const T& MyVector<T>::front() const {
    return m_data[0];
};

template<typename T>
T& MyVector<T>::back() {
	if (length() == 0) {
		return m_data[length()];
	}
    return m_data[length()-1];
};

template<typename T>
const T& MyVector<T>::back() const {
	if (length() == 0) {
		return m_data[length()];
	}
    return m_data[length()-1];
};


// START Capacity

// need to test later. perhaps check if !m_data?
template<typename T>
bool MyVector<T>::empty() {
    return length() == 0;
};

template<typename T>
const bool MyVector<T>::empty() const {
    return length() == 0;
}

template<typename T>
int MyVector<T>::size() {
	return m_length;
}

template<typename T>
const int MyVector<T>::size() const {
    if (length() == 0) {
        return 0;
    }
    return length() - 1;
}

template<typename T>
double MyVector<T>::max_size() {
    int logsize = sizeof(T); // log base 2
    int count = 0;
    while (logsize != 1) {
        logsize /= 2;
        ++count;
    }
    return pow(2,64-count)-1; // assumes 64-bit machine 
};



template<typename T>
const double MyVector<T>::max_size() const {
    int logsize = sizeof(T); // log base 2
    int count = 0;
    while (logsize != 1) {
        logsize /= 2;
        ++count;
    }
    std::cout << "count is: " << count << "\n";
    return pow(2,64-count)-1; // assumes 64-bit machine 
};

template<typename T>
void MyVector<T>::reserve( int newcap) {
	// does nothing if newcap < capacity
    if (newcap > m_trueSize) {
        T* temp = new T[newcap];
        memcpy(temp, m_data, length() * sizeof(T));
        delete m_data;
        m_data = temp;
        m_trueSize = newcap;
        // m_length stays the same
    }
};

template<typename T>
int MyVector<T>::capacity() {
    return m_trueSize;
};

template<typename T>
const int MyVector<T>::capacity() const {
    return m_trueSize;
};

template<typename T>
void MyVector<T>::shrink_to_fit() {
    if (capacity() == length()) {
        // do nothing
    }
    else {
        T* temp = new T[length()];
        memcpy(temp, m_data, m_length * sizeof(T));
        delete m_data;
        m_data = temp;
        m_trueSize = length();
    }
};

// START Modifiers
template<typename T>
void MyVector<T>::clear() {	
	T* temp = new T[capacity()];
	delete m_data;
	m_data = temp;
	m_length = 0;
	// capacity remains the same
};

// inserts 'count' copies of value before index pos
template<typename T>
void MyVector<T>::insert( int pos, int count, const T& value ) {
	int finalSize = m_length + count;
	// first check if we have to resize
	// we do a while loop until finalsize can be contained within capacity
	while (finalSize > capacity()) {
		incCapacity();
	}

	T* temp = new T[capacity()];
	memcpy(temp, m_data, pos * sizeof(T));
	int numCopied = pos;
	for (int ii = 0; ii < count; ++ii) {
		temp[ii + pos] = value;
		++numCopied;
	}
	memcpy(temp + numCopied, m_data + pos, (m_length - pos) * sizeof(T));
	delete m_data;
	m_data = temp;
	m_length = finalSize;
	// capacity remains the same
};


// deletes element at pos
template<typename T>
void MyVector<T>::erase( int pos ) {
	memcpy(m_data + pos, m_data + pos + 1, (m_length - pos) * sizeof(T));

	if (isQuarterEmpty()) {
		decCapacity();
	}
	--m_length;
}

// deletes elements in range [first:last)
template<typename T>
void MyVector<T>::erase( int first, int last){
	memcpy(m_data + first, m_data + last, (m_length - last) * sizeof(T));

	int numDeleted = last - first;
	m_length -= numDeleted;
	if (isQuarterEmpty()) {
		decCapacity();
	}
}

// appends element to end of container
template<typename T>
void MyVector<T>::push_back( const T& value ){
	// verify we're not going to overflow
	if (length() == capacity()) {
		incCapacity();
	}

	m_data[length()] = value;
	m_length += 1;
}

// removes last 
template<typename T>
void MyVector<T>::pop_back() {
	m_length -= 1;
	if (isQuarterEmpty()) {
		decCapacity();
	}
}

template<typename T>
void MyVector<T>::resize( int count ) {
	if (count <= capacity()) {
		m_length = count; // "forget" the indices past count

		// check low capacity usage
		if (isQuarterEmpty()) {
			decCapacity();
		}
	}
	else {
		reserve(count);
	}
}

// this function does not reduce capacity
template<typename T>
void MyVector<T>::resize( int count, const T& value ) {
	if (count <= capacity()) {
		m_length = count; // "forget" the indices past count

		// resize if low capacity usage
		if (isQuarterEmpty()) {
			decCapacity();
		}
	}
	else {
		reserve(count);
		for (int ii = m_length; ii < count; ++ii) {
			m_data[ii] = value;
		m_length = count;
		}
	}
}

template<typename T>
void MyVector<T>::swap( MyVector& other ) {
	MyVector<T> tempVec(m_data, m_length);
	tempVec.reserve(capacity());
	*this = other;
	other = tempVec; 
	// no need to delete tempVec.m_data here because delete will be called when local tempVec 
	// is destroyed at the end of the function 
}

// START Operators

/*RULES FOR LEXICOGRAPHICAL COMPARE
1) compare all indices from start to end
2) the first pair of indices that is different decides the operation
3) all else being equal, shorter is smaller. This program compares both length and capacity*/

template<typename T>
bool MyVector<T>::operator==( const MyVector& rhs) {
	int shorterLength;

	if (length() < rhs.length()) {
		shorterLength = length();
	}
	else {
		shorterLength = rhs.length();
	}

	for (int ii=0; ii<shorterLength; ++ii) {
		if (m_data[ii] == rhs.m_data[ii]) {
			continue;
		}
		else {
			return false;
		}
	}

	// are lengths equivalent? 
	if (length() != rhs.length()) {
		return false;
	}

	// are capacities equivalent? 
	if (capacity() != rhs.capacity()) {
		return false;
	}

	// if you've made it this far, they're equal!
	return true;
}


template<typename T>
bool MyVector<T>::operator!=( const MyVector& rhs) {
	return !(*this==rhs);
}

template<typename T>
bool MyVector<T>::operator<(  const MyVector& rhs) {
	int shorterLength;

	if (length() < rhs.length()) {
		shorterLength = length();
	}
	else {
		shorterLength = rhs.length();
	}

	for (int ii=0; ii<shorterLength; ++ii) {
		if (m_data[ii] < rhs.m_data[ii]) {
			return true;
		}
		else {
			continue;
		}
	}
	// are lengths equivalent? 
	if (length() < rhs.length()) {
		return true;
	}

	// are capacities equivalent? 
	if (capacity() < rhs.capacity()) {
		return true;
	}
	// if you've made it this far, they're equal!
	return false;
}

template<typename T>
bool MyVector<T>::operator<=( const MyVector& rhs) {
	return (!(*this > rhs));
}

template<typename T>
bool MyVector<T>::operator>( const MyVector& rhs) {
	int shorterLength;

	if (length() < rhs.length()) {
		shorterLength = length();
	}
	else {
		shorterLength = rhs.length();
	}

	for (int ii=0; ii<shorterLength; ++ii) {
		if (m_data[ii] > rhs.m_data[ii]) {
			return true;
		}
		else {
			continue;
		}
	}

	// are lengths equivalent? 
	if (length() > rhs.length()) {
		return true;
	}

	// are capacities equivalent? 
	if (capacity() > rhs.capacity()) {
		return true;
	}

	// if you've made it this far, they're equal!
	return false;
}

template<typename T>
bool MyVector<T>::operator>=( const MyVector& rhs) {
	return (!(*this < rhs));
}


// START Misc personal functions
template<typename T>
void MyVector<T>::printVec() {
    // std::cout << "The contents of the vector are listed below:\n";
    for (int ii = 0; ii < length(); ++ii) {
        std::cout << m_data[ii] << " ";
    }
    std::cout << "\n";
};

template<typename T>
const int MyVector<T>::length() const {
    return m_length;
}

template<typename T>
void MyVector<T>::incCapacity() {
	int newCap = m_trueSize * 2;
	T* temp = new T[newCap];
	memcpy(temp, m_data, m_length * sizeof(T));
	delete m_data;
	m_trueSize = newCap;
	m_data = temp;
	// m_length stays the same
};

template<typename T>
void MyVector<T>::decCapacity() {
	int newCap = m_trueSize / 2;
	T* temp = new T[newCap];
	memcpy(temp, m_data, m_length * sizeof(T));
	delete m_data;
	m_trueSize = newCap;
	m_data = temp;
	// m_length stays the same};
};

template<typename T>
bool MyVector<T>::isQuarterEmpty() {
	return m_length <= (capacity()/4);
};

// Template Declarations
#define DECLARE(type) template class MyVector<type>;
DECLARE(int);
DECLARE(float);
DECLARE(char);


