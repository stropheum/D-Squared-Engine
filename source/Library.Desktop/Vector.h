#pragma once
#include "pch.h"

template <class T> class Vector
{
public:
	class Iterator;
	Vector();
	~Vector();
	Vector(const Vector& rhs);
	Vector& operator=(const Vector& rhs);

	Iterator find(const T& value);
	Iterator begin();
	Iterator end();

	T& front();
	T& back();
	T& at(int32_t index);
	T& operator[];
	
	int32_t size();
	int32_t capacity();

	bool isEmpty();

	void popBack();
	void pushBack(const T& value);
	void reserve(int32_t capacity);
	void clear();
	void remove(const T& value);
private:
	T* mBuffer;
	int32_t mSize;
	int32_t mCapacity;
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