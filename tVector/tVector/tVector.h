#pragma once
//tvector class
template <typename T>
class tVector
{
	const static size_t GROWTH_FACTOR = 2;

	T* arr;
	size_t arrSize;
	size_t arrCapacity;

public:
	tVector();
	~tVector();

	void push_back(const T& value);

	T& at(size_t index);
	//iterator class
	class iterator
	{
		tVector* vector;
		size_t cur;

	public:
		//init empty iterator
		iterator();
		iterator(tVector* vec, size_t start);

		bool operator ==(iterator rhs);
		bool operator !=(iterator rhs);
		T& operator*() const;
		T& operator++();
		T operator++(int);
	};

	iterator begin();
	iterator end();
};

template <typename T>
tVector<T>::iterator::iterator()
{
	vector = nullptr;
	cur = 0;
}
template <typename T>
tVector<T>::iterator::iterator(tVector* vec, size_t start)
{
	vector = vec;
	cur = start;
}

template <typename T>
bool tVector<T>::iterator::operator ==(iterator rhs)
{
	return (vector == rhs.vector) && (cur == rhs.cur);
}
template <typename T>
bool tVector<T>::iterator::operator !=(iterator rhs)
{
	return (vector != rhs.vector) || (cur != rhs.cur);
}

template<typename T>
T& tVector<T>::iterator::operator*() const
{
	return &vector[];
}

template <typename T>
T& tVector<T>::iterator::operator++()
{
	return &vector[++cur];
}
template <typename T>
T tVector<T>::iterator::operator++(int)
{
	return &vector[cur++];
}

// returns an iterator pointing to the beginning of the vector
template <typename T>
typename tVector<T>::iterator tVector<T>::begin()
{
	return iterator(this, 0);
}
// returns an iterator pointing after the last element of the vector
template <typename T>
typename tVector<T>::iterator tVector<T>::end()
{
	return iterator(this, arrSize);
}

template <typename T>
tVector<T>::tVector()
{
	arr = new T[1];
	arrSize = 0;
	arrCapacity = 1;
}

template <typename T>
tVector<T>::~tVector()
{
	delete[] arr;
}
template <typename T>
void tVector<T>::push_back(const T& value)
{
	if (arrSize >= arrCapacity)
	{
		arrCapacity *= GROWTH_FACTOR;
		T* newData = new T[arrCapacity];

		for (size_t i = 0; i < arrSize; ++i)
		{
			newData[i] = arr[i];
		}

		delete[] arr;

		arr = newData;
	}

	arr[arrSize] = value;
	++arrSize;
}

template <typename T>
T& tVector<T>::at(size_t index)
{
	return arr[index];
}