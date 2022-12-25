#pragma once

#include <stdlib.h>
#include <utility>

constexpr int STARTING_CAPACITY = 8;
constexpr double CAPACITY_INCREASE_COEF = 2.0;

template<typename T>
class Array final
{
public:
	class Iterator final
	{
		friend Array;

	private:
		T* ptr;
		Array* container;
		int direction;

	public:
		const T& get() const 
		{
			return *ptr;
		}
		void set(const T& value) 
		{
			ptr->~T();
			new (ptr) T(value);
		}
		void next() 
		{
			ptr += direction;
		}
		bool hasNext() const 
		{
			return ptr + direction >= container->_arr && ptr + direction < container->_arr + container->_size;
		}
	};
	class ConstIterator final
	{
		friend Array;

	private:
		T* ptr;
		Array* container;
		int direction;

	public:
		const T& get() const
		{
			return *ptr;
		}
		void next()
		{
			ptr += direction;
		}
		bool hasNext() const 
		{
			return ptr + direction >= container->_arr && ptr + direction < container->_arr + container->_size;
		}
	};

private:
	int _size;
	int _capacity;
	T* _arr;

public:
	Array();
	Array(int capacity);
	Array(const Array& other);
	Array(Array&& other);
	~Array();

	const T& operator[](int index) const
	{
		return _arr[index];
	}
	T& operator[](int index)
	{
		return _arr[index];
	}
	int size() const
	{
		return _size;
	}
	int capacity() const
	{
		return _capacity;
	}

	void swap(Array& other);
	Array& operator=(Array other);
	Array& operator=(Array&& other);
	int insert(const T& value);
	int insert(int index, const T& value);
	void remove(int index);
	Iterator iterator();
	ConstIterator iterator() const;
	Iterator reverseIterator();
	ConstIterator reverseIterator() const;
};

template<typename T>
Array<T>::Array()
{
	_size = 0;
	_capacity = STARTING_CAPACITY;

	_arr = (T*)malloc(_capacity * sizeof(T));
}

template<typename T>
Array<T>::Array(int capacity)
{
	_size = 0;
	if (capacity > 0) 
		this->_capacity = capacity;
	else 
		this->_capacity = STARTING_CAPACITY;
	
	_arr = (T*)malloc(this->_capacity * sizeof(T));
}

template<typename T>
Array<T>::Array(const Array& other)
{
	_size = other._size;
	_capacity = other._capacity;

	_arr = (T*)malloc(other._capacity * sizeof(T));
	for (int i = 0; i < other._size; i++)
		new (_arr + i) T(other._arr[i]);
}

template<typename T>
Array<T>::Array(Array&& other)
{
	_size = other._size;
	_capacity = other._capacity;
	_arr = other._arr;

	other._size = 0;
	other._capacity = 0;
	other._arr = nullptr;
}

template<typename T>
Array<T>::~Array()
{
	for (int i = 0; i < _size; i++)
		_arr[i].~T();

	if (_arr)
		free(_arr);
}

template<typename T>
void Array<T>::swap(Array& other)
{
	std::swap(_size, other._size);
	std::swap(_capacity, other._capacity);
	std::swap(_arr, other._arr);
}

template<typename T>
Array<T>& Array<T>::operator=(Array other)
{
	swap(other);
	return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(Array&& other)
{
	_size = other._size;
	_capacity = other._capacity;
	_arr = other._arr;

	other._size = 0;
	other._capacity = 0;
	other._arr = nullptr;

	return *this;
}

template<typename T>
int Array<T>::insert(const T& value)
{
	if (_size == _capacity) 
	{
		_capacity *= CAPACITY_INCREASE_COEF;
		T* newArr = (T*)malloc(_capacity * sizeof(T));

		for (int i = 0; i < _size; i++) 
		{
			new (newArr + i) T(std::move(_arr[i]));
			_arr[i].~T();
		}

		free(_arr);
		_arr = newArr;
	}

	new (_arr + _size) T(value);

	return _size++;
}

template<typename T>
int Array<T>::insert(int index, const T& value)
{
	if (index < 0 || index >= _size)
		return insert(value);

	if (_size == _capacity) 
	{
		_capacity *= CAPACITY_INCREASE_COEF;
		T* newArr = (T*)malloc(_capacity * sizeof(T));

		for (int i = 0; i < index; i++) 
		{
			new (newArr + i) T(std::move(_arr[i]));
			_arr[i].~T();
		}

		new (newArr + index) T(value);

		for (int i = index; i < _size; i++) 
		{
			new (newArr + i + 1) T(std::move(_arr[i]));
			_arr[i].~T();
		}

		free(_arr);
		_arr = newArr;
	}
	else 
	{
		//TODO: create test for that V - done
		//TODO: arr[_size] contains garbage - done
		for (int i = _size; i > index; i--)
		{
			new (_arr + i) T(std::move(_arr[i - 1]));
			_arr[i - 1].~T();
		}

		new (_arr + index) T(value);
	}

	_size++;
	return index;
}

template<typename T>
void Array<T>::remove(int index)
{
	if (index < 0 || index >= _size)
		return;

	_arr[index].~T();

	// TODO: garbage at _arr[index] - done
	for (int i = index; i < _size - 1; i++)
	{
		new (_arr + i) T(std::move(_arr[i + 1]));
		_arr[i + 1].~T();
	}

	_size--;
}

template<typename T>
typename Array<T>::Iterator Array<T>::iterator()
{
	Iterator iter;
	iter.ptr = _arr;
	iter.container = this;
	iter.direction = 1;
	return iter;
}

template<typename T>
typename Array<T>::ConstIterator Array<T>::iterator() const
{
	ConstIterator iter;
	iter.ptr = _arr;
	iter.container = this;
	iter.direction = 1;
	return iter;
}

template<typename T>
typename Array<T>::Iterator Array<T>::reverseIterator()
{
	Iterator iter;
	iter.ptr = _arr + _size - 1;
	iter.container = this;
	iter.direction = -1;
	return iter;
}

template<typename T>
typename Array<T>::ConstIterator Array<T>::reverseIterator() const
{
	ConstIterator iter;
	iter.ptr = _arr + _size - 1;
	iter.container = this;
	iter.direction = -1;
	return iter;
}