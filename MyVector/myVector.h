#pragma once

#include <iostream>
#include <functional>
#include <algorithm>
#include <exception>
#include <utility>     

template<typename T>
class myVector{

private:
	T* m_data = nullptr;
	
	size_t m_size = 0;
	size_t m_cap = 0;

public:

	myVector() {
		ReAlloc(2);
		
	}	
	myVector(int cap) {
		ReAlloc(cap);
	}

	~myVector() {
		reset();
		::operator delete(m_data, m_cap * sizeof(T));
	}
	
	//Reallocate more space as needed
	void ReAlloc(size_t newCapacity) {

		T* newBlock = (T*)::operator new(newCapacity * sizeof(T));
		
		for (size_t i = 0; i < m_size; ++i) {
			newBlock[i] = std::move(m_data[i]);
		}
				
		for (size_t i = 0; i < m_size; ++i) {
			m_data[i].~T();
		}

		::operator delete(m_data, m_cap * sizeof(T));

		m_data = newBlock;
		m_cap = newCapacity;
	}

	//push back operation
	void add(const T& val) { 
		if (m_size == m_cap) {
			ReAlloc(m_cap + 2);
		}
		m_size++;
		m_data[m_size-1] = val;		
	}

	//push back operation that takes an arguement list
	template<typename... Args>
	void add(const T& val, const Args&... args) {
		add(val);
		add(args...);
	}

	//Add all elements within an iterable container
	template<typename container> 
	void addElementsOf(const container& c) {
		auto it = std::begin(c);
		for (it; it < std::end(c); ++it) {
			add(*it);
		}
	}

	//add an element at a specific index FIX
	void addAt(int index, const T& val) {
		if (index < 0 || index >= m_size)
			throw std::string("Out of bounds!");

		if (m_size == 0)
			return add(val);
		//size is atleast 1
		if (m_size == m_cap) {
			ReAlloc(m_cap + 2);
		}
		//shift everything from index one space to the right
		++m_size;

		if (m_size == 1)
			return add(val);
		//size atleast 2

		int nxtPtr = m_size-2; //max value of next is m_Size - 1

		for (size_t i = m_size-1; i > index; --i) {
			m_data[i] = m_data[nxtPtr]; //shifts everything to the right
			nxtPtr--;
		}
		m_data[index] = val; // put element right where it should be. 

	}
	
	//remove index i; // returns success or failure
	bool remove(size_t index) {
		if (index < 0 || index >= m_size) 
			return false;
	
		size_t nxt;
		for (size_t i = index; i < m_size; ++i) {
			nxt = i + 1;
			if (nxt >= m_size)// next is now pointing to the last element of the resized vect
				break;
			m_data[i] = m_data[nxt];
		}
		m_data[m_size - 1].~T(); //delete last element if element is an object. 

		m_size -= 1;
		return true;
	}

	//remove a T value returns success or failure
	bool removeElement(T value) {
		size_t index = find(value);
		if (index < 0)
			return false;
		return remove(index);
	}

	//remove all instances of an element
	void removeAll(const T& val) {
		while (removeElement(val)) {}
	}

	//return index of an element. 
	size_t find(const T& value) {
		for (size_t i = 0; i < getSize(); ++i) {
			if (m_data[i] == value)
				return i;
		}
		return size_t(-1); //failure
	}

	//begin and end pointers
	T* begin() const{ return m_data; }	
	T* end()  const{ return (m_data + m_size);}

	//overloading the subscript operator
	T& operator [] (size_t index) const {
		if (index < 0 || index >= m_size) 
			throw std::string("Out of bounds!");
		else
			return *(m_data + index);
	}
	
	//returns true if vector contains value
	bool contains(const T& val) const {
		T* p = std::find(begin(), end(), val);
		if (p == end())
			return false; 
		return true;
	}

	//returns true if vector contains list of arguements
	template<typename ...Args>
	bool contains(const T& val, const Args&... args) const {
		if (!contains(val))
			return false;
		contains(args...);
	}

	void reset() {
		for (size_t i = 0; i < m_size; ++i) {
		//	m_data[i].~T();
		}
		m_size = 0;
		ReAlloc(2); // reduce allocation to two spaces, deleting the rest
	}

	//removes elements in range [left,right] including left and right indices
	void erase(size_t left, size_t right) {
		if(left < 0 || left >= m_size || right < 0 || right >= m_size)
			throw std::string("Out of bounds!");

		T* newPtr = (T*)::operator new(sizeof(T) * m_cap);
		size_t newSize = m_size - ((right - left) + 1); 

		size_t indexP = 0;
		for (size_t i = 0; i <= m_size; ++i) { //only copy element not in that range
			if (i < left || i > right) {
				newPtr[indexP] = std::move(m_data[i]);
				++indexP;
			}
		}

		for (size_t i = 0; i <= m_size; ++i)
			m_data[i].~T();
		
		::operator delete(m_data, m_cap * sizeof(T));


		m_data = newPtr;
		m_size = newSize;		
	}

	void swap(myVector& other) {
		//resize the smaller of the two
		
		size_t sz = m_size;
		size_t osz = other.getSize();
		size_t i = 0;
		size_t j = 0;
		while (i < sz && j < osz) {
			T tmp = other[j];
			other[j] = m_data[i];
			m_data[i] = tmp;
			++i;
			++j;
		}		
		while (i < sz) {
			other.add(m_data[i]);
			++i;
		}		
		while (j < osz) {
			add(other[j]);
			++j;
		}
		resize(osz);
		other.resize(sz);


	}

	void resize(size_t newSize) {

		if (newSize < 0 || newSize >= m_size)
			return;

		T* newPtr = (T*)::operator new(sizeof(T) * m_cap);
		//size_t newSize = m_size - ((right - left) + 1);

		for (size_t i = 0; i < newSize; ++i) { //only copy element not in that range
			newPtr[i] = std::move(m_data[i]);
		}


		for (size_t i = 0; i <= m_size; ++i)
			m_data[i].~T();

		::operator delete(m_data, m_cap * sizeof(T));


		m_data = newPtr;
		m_size = newSize;
	}

	//getters
	size_t getSize() const { return m_size; }
	bool isEmpty()   const { return m_size == 0 ? true : false; }

};


