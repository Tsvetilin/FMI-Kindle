#pragma once

template <typename T>
class List {
	T* data;
	size_t capacity;
	size_t count;

public:
	List();
	bool contains(const T& element) const;
	void add(const T& element);
	T& at(size_t ind) const;

	size_t getCount()const {
		return count;
	}

	T& operator[](size_t index)const {
		return at(index);
	}

};

template <typename T>
List<T>::List(){
	count = 0;
	capacity = 10;
	data = new T[capacity];
}

template <typename T>
T& List<T>::at(size_t ind) const {
	if (ind >= count) {
		throw "Index out of range exception.";
	}

	return data[ind];
}

template <typename T>
void List<T>::add(const T& element) {
	if (capacity == count) {
		capacity *= 2;
		T* newArr = new T[capacity];
		for (size_t i = 0; i < count; i++)
		{
			newArr[i] = data[i];
		}
		delete[] data;
		data = newArr;
	}

	data[count++] = element;
}

template <typename T>
bool List<T>::contains(const T& element)const {
	for (size_t i = 0; i < count; i++)
	{
		if (data[i] == element) {
			return true;
		}
	}

	return false;
}