#pragma once
#define DEFAULT_CAPACITY 10
#define RESIZE_FACTOR 2

template <typename T>
class List {
	T* data;
	size_t capacity;
	size_t count;

	void copyFrom(const List& other);
	void free();

public:
	List();
	List(const List& other);
	List& operator= (const List& other);
	~List();

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
void List<T>::copyFrom(const List& other) {
	count = other.count;
	capacity = other.capacity;
	data = new T[capacity];
	for (size_t i = 0; i < count; i++)
	{
		data[i] = other.data[i];
	}
}

template <typename T>
void List<T>::free() {
	delete[] data;
}

template <typename T>
List<T>::List() {
	count = 0;
	capacity = DEFAULT_CAPACITY;
	data = new T[capacity];
}

template <typename T>
List<T>::List(const List& other) {
	copyFrom(other);
}

template <typename T>
List<T>& List<T>::operator= (const List<T>& other) {
	if (this != &other) {
		copyFrom(other);
		free();
	}

	return *this;
}

template <typename T>
List<T>::~List() {
	free();
}

template <typename T>
T& List<T>::at(size_t ind) const {
	if (ind >= count) {
		throw std::invalid_argument("Index out of range exception.");
	}

	return data[ind];
}

template <typename T>
void List<T>::add(const T& element) {
	if (capacity == count) {
		capacity *= RESIZE_FACTOR;
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