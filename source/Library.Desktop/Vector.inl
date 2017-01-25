#pragma once
#include "pch.h"
#include <new>

template <typename T>
Vector<T>::Vector() :
	mBuffer(nullptr), mSize(0), mCapacity(10)
{
	reserve(mCapacity);
}

template <typename T>
Vector<T>::~Vector()
{
	//TODO: Delete any heap allocated memory
	//TODO: Deconstruct all T's in mBuffer
	clear();
}

template <typename T>
Vector<T>::Vector(const Vector<T>& rhs) :
	mBuffer(nullptr), mSize(rhs.mSize), mCapacity(rhs.mSize)
{
	reserve(mCapacity);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs) 
{
	//TODO: Implement assignment operator
	return const_cast<Vector&>(rhs);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::find(const T& value)
{
	//TODO: Implement assignment operator
	return this;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin()
{
	//TODO: Implement begin method
	return Iterator();
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end()
{
	//TODO: Implement end method
	return Iterator();
}

template <typename T>
T& Vector<T>::front()
{
	return mBuffer;
}

template <typename T>
T& Vector<T>::back()
{
	return mBuffer + (sizeof(T)*(mSize - 1));
}

template <typename T>
T& Vector<T>::at(const uint32_t index)
{
	return operator[](index);
}

template <typename T>
T& Vector<T>::operator[](const uint32_t index)
{
	if (index >= mSize) throw std::exception("Index out of bounds");
	return *(mBuffer + index);
}

template <typename T>
uint32_t Vector<T>::size() const
{
	return mSize;
}

template <typename T>
uint32_t Vector<T>::capacity() const
{
	return mCapacity;
}

template <typename T>
bool Vector<T>::isEmpty()
{
	//TODO: Implement isEmpty method
	bool result = true;
	return result;
}

template <typename T>
void Vector<T>::popBack()
{
	//TODO: Implement popBack method
	int temp = 0;
}

template <typename T>
void Vector<T>::pushBack(const T& value)
{
	//TODO: Expand if size matches capacity
	if (mSize < mCapacity)
	{
		new(mBuffer+mSize++) T(value);
	}
	else
	{
		throw std::exception("Attempting to push back with no available capacity. Resizing not yet implemented");
	}
}

template <typename T>
void Vector<T>::reserve(uint32_t capacity)
{
	if (capacity > mSize && capacity >= mCapacity)
	{
		T* temp = mBuffer;
		mBuffer = static_cast<T*>(malloc(sizeof(T) * capacity));
		memcpy_s(mBuffer, sizeof(T) * mSize, temp, sizeof(T) * mSize);
		free(temp);
		mCapacity = capacity;
	}
}

template <typename T>
void Vector<T>::clear()
{
	for (uint32_t i = 0; i < mSize; i++)
	{
		(mBuffer + i)->~T();
	}
	free(mBuffer);
	mSize = mCapacity = 0;
}

template <typename T>
void Vector<T>::remove(const T& value)
{
	//TODO: Implement remove method
}

/// //////////////////////////////// ///
///  Vector Iterator implementation  ///
/// //////////////////////////////// ///

template <typename T>
Vector<T>::Iterator::Iterator() {}

template <typename T>
Vector<T>::Iterator::Iterator(const T& value) :
	mValue(value) {}

template <typename T>
Vector<T>::Iterator::Iterator(const Iterator& rhs)
{
	//TODO: Implement copy constructor
}

template <typename T>
bool Vector<T>::Iterator::operator==(const Iterator& rhs)
{
	//TODO: Implement operator==()
	return true;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
{
	//TODO: Implement increment operator
	return this;
}

template <typename T>
T& Vector<T>::Iterator::operator*()
{
	//TODO: Implement dereference operator
	T t{};
	return t;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& rhs)
{
	//TODO: Implement assignment operator
	return this;
}