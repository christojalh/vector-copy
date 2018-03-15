// questions
//  -what does this line do again? (at bottom of program) #define DECLARE(type) template class MyVector<type>;
//	-what are all the steps in defining a template class again?
//	-is there a better way to use parent variables besides doing
//		"parent->variablename" all the time?
//	-how do you "disable" operators? I've currently set the operators to be void

/* Christopher Lee	   
 * February 26th, 2018
 * Last updated: March 12th, 2018
 * 
 * This program is a copy class of std::vector with reduced constructor functionality
 * To create a vector using this program, pass in an array of data and the length of the array
 * 
 * Functions included:
 * -Element access
 * -Capacity
 * -Modifiers
 * -Lexicographical compare operators (==, !=, >=, >, <=, <)
 * -Iterators 
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


template<typename T>
std::ostream& operator<< (std::ostream& os, const MyVector<T>& vec) {
    for (int ii = 0; ii < vec.length(); ++ii) {
        os << vec[ii] << " ";
    }
    os << "\n";

    return os;
}

// START Member functions
// Constructor
template<typename T>
MyVector<T>::MyVector(T* input,int length) {
    m_length = length;
    m_trueSize = m_length;
    m_data = new T[m_length];
    memcpy(m_data, input, m_length * sizeof(T));

    // The pointers contained in m_instChecker are the first
    // invalid index for that instance
    m_instChecker = new T*[1];
    m_instChecker[0] = m_data + m_length;
    m_instCapacity = 1;
    m_currentInst = 0;
    m_firstValidInst = 0;
    m_createNewInst = false;

}

// Destructor
template<typename T>
MyVector<T>::~MyVector() {
    delete m_data;
    delete m_instChecker;
}

// *** case: capacity changes -> all invalidated
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

    m_createNewInst = true;
    updInvalid();

}

// *** case: capacity changes -> all invalidated
template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    T* temp = new T[other.capacity()];
    memcpy(temp, other.m_data, other.length() * sizeof(T));
    delete m_data;
    m_data = temp;
    m_length = other.length();
    m_trueSize = other.capacity();

    m_createNewInst = true;
    updInvalid();
}


// START Element access
template<typename T>
T& MyVector<T>::operator[]( int pos ) {
    return m_data[pos];
};

template<typename T>
const T& MyVector<T>::operator[]( int pos ) const {
    return m_data[pos];
};

template<typename T>
T& MyVector<T>::at( int pos ) {
    if (pos < 0 || pos >= length()) {
        throw std::out_of_range("Index out of bounds\n");
    }
    return m_data[pos];
};

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

// *** case: capacity changes -> all invalidated
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

        m_createNewInst = true;
        updInvalid();
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

// *** capacity changes -> all invalidated
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

        m_createNewInst = true; 
        updInvalid();
    }
};

// START Modifiers
// ***  case: new m_data -> all invalidated
template<typename T>
void MyVector<T>::clear() {	
	T* temp = new T[capacity()];
	delete m_data;
	m_data = temp;
	m_length = 0;
	// capacity remains the same

	m_createNewInst = true; 
	updInvalid();
};

// inserts 'count' copies of value before index pos
// *** case: capacity changes -> all invalidated
// *** case: insertion -> iterators after insertion invalidated
template<typename T>
void MyVector<T>::insert( int pos, int count, const T& value ) {
	int finalSize = m_length + count;
	// first check if we have to resize
	// we do a while loop until finalsize can be contained within capacity
	while (finalSize > capacity()) {
		incCapacity();
	}

	int numAfterPos = length() - pos; // indices to append after insertion
	T* temp = new T[numAfterPos];
	memcpy(temp, m_data + pos, numAfterPos * sizeof(T));

	for (int ii = 0; ii < count; ++ii) {
		m_data[ii + pos] = value;
	}

	memcpy(m_data + pos + count, temp, numAfterPos * sizeof(T));
	delete temp;
	m_length = finalSize;
	// capacity remains the same

	m_createNewInst = true; 
	T* invalidPos = m_data + pos;
	// We're only going to update m_instChecker if the current
	// pointer is further in the array than the new one, otherwise
	// we'll be de-invalidating indices
	if (m_instChecker[m_currentInst] > invalidPos) {
		m_instChecker[m_currentInst] = invalidPos;		
	}
}; 


// deletes element at pos
// case: insertion -> iterators after insertion invalidated
// possible case: capacity decreases -> all current its invalidated
template<typename T>
void MyVector<T>::erase( int pos ) {
	memcpy(m_data + pos, m_data + pos + 1, (m_length - pos) * sizeof(T));

	if (isQuarterEmpty()) {
		decCapacity();
	}
	--m_length;

	m_createNewInst = true; 
	T* invalidPos = m_data + pos;
	if (m_instChecker[m_currentInst] > invalidPos) {
		m_instChecker[m_currentInst] = invalidPos;		
	}
}

// deletes elements in range [first:last)
// case: insertion -> iterators after insertion invalidated
// possible case: capacity decreases -> all current its invalidated
template<typename T>
void MyVector<T>::erase( int first, int last){
	memcpy(m_data + first, m_data + last, (m_length - last) * sizeof(T));

	int numDeleted = last - first;
	m_length -= numDeleted;
	while (isQuarterEmpty()) {
		decCapacity();
	}

	m_createNewInst = true; 
	T* invalidPos = m_data + first;
	if (m_instChecker[m_currentInst] > invalidPos) {
		m_instChecker[m_currentInst] = invalidPos;		
	}
}

// appends element to end of container
// *** possible case: capacity -> all current iterators invalidated
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
// *** case: insertion -> iterators after insertion invalidated
// *** possible case: capacity -> all current iterators invalidated
template<typename T>
void MyVector<T>::pop_back() {
	if (length() < 0) {
		return;
	}
	m_length -= 1;
	if (isQuarterEmpty()) {
		decCapacity();
	}

	m_createNewInst = true; 
	T* invalidPos = m_data + length() - 1;
	if (m_instChecker[m_currentInst] > invalidPos) {
		m_instChecker[m_currentInst] = invalidPos;		
	}	
}

// *** possible case: capacity -> all current iterators invalidated
// *** possible case: deletion -> iterators after are invalidated
template<typename T>
void MyVector<T>::resize( int count ) {
	if (count <= capacity()) {
		if (count < m_length) {
			m_length = count; // "forget" the indices past count
			
			m_createNewInst = true; 
			T* invalidPos = m_data + count;
			if (m_instChecker[m_currentInst] > invalidPos) {
				m_instChecker[m_currentInst] = invalidPos;		
			}	

			// check low capacity usage
			if (isQuarterEmpty()) {
				decCapacity();
			}
		}
		else {
			// do nothing, since the desired size is accounted for by
			// capacity() and no indices need to be "forgotten"
		}
	}
	else {
		reserve(count);
		// iterator invalidation carried out by reserve()
	}
}

// *** possible case: capacity -> all current iterators invalidated
template<typename T>
void MyVector<T>::resize( int count, const T& value ) {
	if (count <= capacity()) {
		if (count < m_length) {
			m_length = count; // "forget" the indices past count

			m_createNewInst = true; 
			T* invalidPos = m_data + count;
			if (m_instChecker[m_currentInst] > invalidPos) {
				m_instChecker[m_currentInst] = invalidPos;		
			}	
			// check low capacity usage
			if (isQuarterEmpty()) {
				decCapacity();
			}
		}
		else {
			// do nothing, since the desired size is accounted for by
			// capacity() and no indices need to be "forgotten"
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

// *** case: reallocation -> all invalidated
template<typename T>
void MyVector<T>::swap( MyVector& other ) {
	MyVector<T> tempVec(m_data, m_length);
	tempVec.reserve(capacity());
	*this = other;
	other = tempVec; 
	// no need to delete tempVec.m_data here because delete will be called when local tempVec 
	// is destroyed at the end of the function 

	m_createNewInst = true; 
	updInvalid();
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

// any time you call this function, all current iterators
// are invalidated
template<typename T>
void MyVector<T>::incCapacity() {
	int newCap = m_trueSize * 2;
	T* temp = new T[newCap];
	memcpy(temp, m_data, m_length * sizeof(T));
	delete m_data;
	m_trueSize = newCap;
	m_data = temp;
	// m_length stays the same

	m_createNewInst = true; 
	updInvalid();
};


template<typename T>
void MyVector<T>::incInstCapacity() {
	int newCap = m_instCapacity * 2;
	T** temp = new T*[newCap];
	memcpy(temp, m_instChecker, m_currentInst * sizeof(T*));
	delete m_instChecker;
	m_instChecker = temp;
	m_instCapacity = newCap;
};

template<typename T>
int MyVector<T>::getInstCapacity() {
	return m_instCapacity;
}

template<typename T>
int MyVector<T>::getCurrentInst() {
	return m_currentInst;
}

// any time you call this function, all current iterators
// are invalidated
template<typename T>
void MyVector<T>::decCapacity() {
	int newCap = m_trueSize / 2;
	T* temp = new T[newCap];
	memcpy(temp, m_data, m_length * sizeof(T));
	delete m_data;
	m_trueSize = newCap;
	m_data = temp;
	// m_length stays the same};

	m_createNewInst = true; 
	updInvalid();
};

template<typename T> bool MyVector<T>::isQuarterEmpty() {
	return m_length <= (capacity()/4);
};

//START Iterator

// This function is called after m_data is reallocated,
// invalidating all existing instances
template<typename T>
void MyVector<T>::updInvalid() {
	m_firstValidInst = m_currentInst + 1;
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::begin() {
    return Iterator(m_data, this);
}

// returns an iterator pointing to one index past the last element
template<typename T>
typename MyVector<T>::Iterator MyVector<T>::end() {
    return Iterator(m_data + m_length, this);
}

template<typename T>
MyVector<T>::Iterator::Iterator(T* index, MyVector<T>* vec) {
	m_index = index;
	parent = vec;
	// if m_data has been changed, createNewInst will be true
	// and we'll increment the current instance
	if (parent->m_createNewInst == true) {
		// first we have to check if instChecker can hold 
		// another instance
		parent->m_currentInst += 1;
		if (parent->m_currentInst == parent->m_instCapacity) {
			parent->incInstCapacity();
		}
		parent->m_createNewInst = false;
		m_inst = parent->m_currentInst;
		parent->m_instChecker[parent->m_currentInst] = (parent->m_data + parent->m_length);
	}
	else {
		m_inst = parent->m_currentInst;
	}
}

template<typename T>
MyVector<T>::Iterator::~Iterator() {

}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator++() {
	if (!isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}
	m_index += 1;
	return *this;
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator--() {
	if (!isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}
	m_index -= 1;
	return *this;
}

template<typename T>
bool MyVector<T>::Iterator::operator==( const typename MyVector<T>::Iterator& rhs) {
	// There are actually two iterators in this operation, 
	// so we have to check both are valid
	if (!isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}	
	if (!rhs.isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}	
	return m_index == rhs.m_index;
}

template<typename T>
bool MyVector<T>::Iterator::operator!=( const typename MyVector<T>::Iterator& rhs) {
	if (!isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}	
	if (!rhs.isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}		
	return m_index != rhs.m_index;
}

template<typename T>
T& MyVector<T>::Iterator::operator*() {
	if (!isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}	
	return (*m_index);
}

template<typename T>	
const bool MyVector<T>::Iterator::isValid() const {
	if (inst() >= parent->m_firstValidInst) {
		if (index() <= parent->m_instChecker[inst()]) {
			return true;
		}
	}
	return false;
}

template<typename T>
int MyVector<T>::Iterator::inst() {
	return m_inst;
}

template<typename T>
const int MyVector<T>::Iterator::inst() const {
	return m_inst;
}

template<typename T>
T* MyVector<T>::Iterator::index() {
	return m_index;
}

template<typename T>
const T* MyVector<T>::Iterator::index() const {
	return m_index;
}

// disable some Iterator operators
template<typename T>
void MyVector<T>::Iterator::operator>( const Iterator& rhs) {
	// do nothing
}

template<typename T>
void MyVector<T>::Iterator::operator>=( const Iterator& rhs) {
	// do nothing
}

template<typename T>
void MyVector<T>::Iterator::operator<( const Iterator& rhs) {
	// do nothing
}

template<typename T>
void MyVector<T>::Iterator::operator<=( const Iterator& rhs) {
	// do nothing
}

template<typename T>
void MyVector<T>::Iterator::operator+( const Iterator& rhs) {
	// do nothing
}

template<typename T>
void MyVector<T>::Iterator::operator-( const Iterator& rhs) {
	// do nothing
}

template<typename T>
void MyVector<T>::Iterator::operator*( const Iterator& rhs) {
	// do nothing
}


// START ReverseIterator
template<typename T>
MyVector<T>::ReverseIterator::ReverseIterator(T* index, MyVector<T>* vec) {
	m_index = index;
	parent = vec;

	if (parent->m_createNewInst == true) {
		if (parent->m_currentInst == parent->m_instCapacity) {
			parent->incInstCapacity();
		}		
		parent->m_currentInst += 1;
		parent->m_createNewInst = false;
		m_inst = parent->m_currentInst;
		parent->m_instChecker[parent->m_currentInst] = (parent->m_data + parent->m_length);
	}
	else {
		m_inst = parent->m_currentInst;
	}
}

template<typename T>
MyVector<T>::ReverseIterator::~ReverseIterator() {

}

// we subtract an index because we are traversing it backwards
// to the client, it's like we are going "forwards" on a 
// reversed array
template<typename T>
typename MyVector<T>::ReverseIterator& MyVector<T>::ReverseIterator::operator++() {
	if (!isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}	
	m_index -= 1;
	return *this;
}

// likewise, add to m_index to decrement
template<typename T>
typename MyVector<T>::ReverseIterator& MyVector<T>::ReverseIterator::operator--() {
	if (!isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}	
	m_index += 1;
	return *this;
}

template<typename T>
bool MyVector<T>::ReverseIterator::operator==( const typename MyVector<T>::ReverseIterator& rhs) {
	if (!isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}	
	if (!rhs.isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}
	return m_index == rhs.m_index;
}

template<typename T>
bool MyVector<T>::ReverseIterator::operator!=( const typename MyVector<T>::ReverseIterator& rhs) {
	if (!isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}	
	if (!rhs.isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}
	return m_index != rhs.m_index;
}

template<typename T>
T& MyVector<T>::ReverseIterator::operator*() {
	if (!isValid()) {
		throw std::invalid_argument( "This iterator is invalid." );
	}	
	return (*m_index);
}

// returns pointer to the final element, which is length() - 1
template<typename T>
typename MyVector<T>::ReverseIterator MyVector<T>::rbegin() {
    return ReverseIterator(m_data + m_length - 1, this);
}

// the end element is one index before the first one
template<typename T>
typename MyVector<T>::ReverseIterator MyVector<T>::rend() {
    return ReverseIterator(m_data - 1, this);
}

// disable some ReverseIterator operators
template<typename T>
void MyVector<T>::ReverseIterator::operator>( const ReverseIterator& rhs) {
	// do nothing
}
template<typename T>
void MyVector<T>::ReverseIterator::operator>=( const ReverseIterator& rhs) {
	// do nothing
}
template<typename T>
void MyVector<T>::ReverseIterator::operator<( const ReverseIterator& rhs) {
	// do nothing
}
template<typename T>
void MyVector<T>::ReverseIterator::operator<=( const ReverseIterator& rhs) {
	// do nothing
}
template<typename T>
void MyVector<T>::ReverseIterator::operator+( const ReverseIterator& rhs) {
	// do nothing
}
template<typename T>
void MyVector<T>::ReverseIterator::operator-( const ReverseIterator& rhs) {
	// do nothing
}
template<typename T>
void MyVector<T>::ReverseIterator::operator*( const ReverseIterator& rhs) {
	// do nothing
}

template<typename T>	
const bool MyVector<T>::ReverseIterator::isValid() const {
	if (inst() >= parent->m_firstValidInst) {
		if (index() <= parent->m_instChecker[inst()]) {
			return true;
		}
	}
	return false;
}

template<typename T>
int MyVector<T>::ReverseIterator::inst() {
	return m_inst;
}

template<typename T>
const int MyVector<T>::ReverseIterator::inst() const {
	return m_inst;
}

template<typename T>
T* MyVector<T>::ReverseIterator::index() {
	return m_index;
}

template<typename T>
const T* MyVector<T>::ReverseIterator::index() const {
	return m_index;
}


// Template Declarations
#define DECLARE(type) template class MyVector<type>;
DECLARE(int);
DECLARE(float);
DECLARE(char);


