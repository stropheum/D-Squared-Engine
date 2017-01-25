#pragma once
#include "pch.h"

template <class T> class Vector
{
public:
	class Iterator;
	Vector();
	Vector(const Vector<T>& rhs);
	Vector(Vector<T>&& rhs);
	Vector<T>& operator=(const Vector<T>& rhs);
	Vector<T>& operator=(Vector&& rhs);
	~Vector();

	Iterator find(const T& value);
	Iterator begin();
	Iterator end();

	T& front();
	T& back();
	T& at(const uint32_t index);
	T& operator[](const uint32_t index);
	T popBack();
	
	std::uint32_t size() const;
	std::uint32_t capacity() const;

	bool isEmpty() const;

	void pushBack(const T& value);
	void reserve(std::uint32_t capacity);
	void clear();
	void remove(const T& value);
private:
	T* mBuffer;
	std::uint32_t mSize;
	std::uint32_t mCapacity;
public:
	class Iterator
	{
	public:
		Iterator();
		bool operator==(const Iterator& rhs);
		Iterator& operator++();
		T& operator*();
		Iterator& operator=(const Iterator& rhs);
	private:
		explicit Iterator(const T& value);
		Iterator(const Iterator& rhs);
		T* mValue;
	};
};

#include "Vector.inl"