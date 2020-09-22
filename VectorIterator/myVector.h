#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>
#include <utility>      // std::move



template<typename T>
class myVector{

private:
	T* m_data = nullptr;
	
	size_t m_size = 0;
	size_t m_cap = 0;

public:

	myVector() {
		std::cout << "Allocated a space of two\n";
		ReAlloc(2);
		
	}	
	myVector(int cap) {
		std::cout << "Allocated a space of " << cap << std::endl;
		ReAlloc(cap);
	}

	~myVector() {
		std::cout << "Class destructor called\n";
		reset();
		::operator delete(m_data, m_size * m_cap);
	}
	

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

	
	void add(const T& val) {
		std::cout << "Curr size: " << m_size << std::endl;
		std::cout << "Curr cap: " << m_cap << std::endl;

		if (m_size == m_cap) {
			ReAlloc(m_cap + 2);
			std::cout << "RECAPED for item \n"; //<< val << "\n";
		}

		m_size++;//m_size;
		m_data[0] = val;	

	}

	template<typename... Args>
	void add(const T& val, Args... args) {
		add(val);
		add(args...);
	}

	
	//remove index i;
	int remove(int index) {
		if (index < 0 || index >= m_size) 
			return -1;
	
		std::cout << "removing by index " << index << std::endl;

		int nxt;
		for (int i = index; i < m_size; ++i) {
			nxt = i + 1;
			if (nxt >= m_size)// next is now pointing to the last element of the resized vect
				break;
			m_data[i] = m_data[nxt];
		}
		m_data[m_size - 1].~T(); //delete last element if element is an object. 
		delete (m_data + (m_size - 1));

		m_size -= 1;
		return 0;
	}

	//remove a T value
	int removeElement(T value) {
		std::cout << "removing by element: " << value << "\n";
		int index = find(value);
		std::cout << "Element is at index: " << index << std::endl;

		if (index < 0)
			return -1;
	
		remove(size_t(index));
		return 0;
	}

	//remove all instances of an element
	
	void removeAll(T val) {
		while (removeElement(val) != -1) {
		};
	}



	//return index of an element. 
	size_t find(T value) {
		for (size_t i = 0; i < getSize(); ++i) {
			if (m_data[i] == value)
				return i;
		}
		return size_t(-1);
	}

	T* begin() const{
		return m_data;
	}	
	T* end()  const{
		return (m_data + m_size);
	}


	T& operator [] (int index) const {
		if (index < 0 || index >= m_size) 
			throw std::string("Out of bounds!");
		else
			return *(m_data + index);
	}
	

	bool contains(const T& val) const {
		T* p = std::find(begin(), end(), val);
		if (p == end())
			return false; 
		return true;
	}

	template<typename ...Args>
	bool contains(const T& val, Args... args) const {

		if (!contains(val))
			return false;

		contains(args...);

	}

	
	
	void reset() {

		for (size_t i = 0; i < m_size; ++i) {
			m_data[i].~T();
		}
		::operator delete(m_data, sizeof(T) * m_cap);
		m_size = 0;

		ReAlloc(2);
	}

	//getters
	size_t getSize() const { return m_size; }

};


