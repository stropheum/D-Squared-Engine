#pragma once
#include "pch.h"
#include "Vector.h"

template <class T>
Vector<T>::Vector() :
	mSize(0), mCapacity(10)
{
	mBuffer = dynamic_cast<T*>(malloc(sizeof(T) * mCapacity));
}

template <class T>
Vector<T>::~Vector()
{
	//TODO: Delete any heap allocated memory
	//TODO: Deconstruct all T's in mBuffer
	free(mBuffer);
}

template <class T>
Vector<T>::Vector(const Vector& rhs) :
	mSize(rhs.mSize), mCapacity(rhs.mSize)
{
	//TODO: Implement copy constructor
}

template <class T>
typename Vector<T>::Vector& Vector<T>::operator=(const Vector& rhs) 
{
	//TODO: Implement assignment operator
	return this;
}

template <class T>
typename Vector<T>::Iterator Vector<T>::find(const T& value)
{
	//TODO: Implement assignment operator
	return this;
}

template <class T>
typename Vector<T>::Iterator Vector<T>::begin()
{
	//TODO: Implement begin method
	return Iterator();
}

template <class T>
typename Vector<T>::Iterator Vector<T>::end()
{
	//TODO: Implement end method
	return Iterator();
}

template <class T>
T& Vector<T>::front()
{
	//TODO: Implement front method
	return T();
}

template <class T>
T& Vector<T>::back()
{
	//TODO: Implement back method
	return T();
}

template <class T>
T& Vector<T>::at(int32_t index)
{
	//TODO: Implement at method
	return T();
}

template <class T>
int32_t Vector<T>::size()
{
	//TODO: Implement size method
	return 0;
}

template <class T>
int32_t Vector<T>::capacity()
{
	//TODO: Implement capacity method
	return 0;
}

template <class T>
bool Vector<T>::isEmpty()
{
	//TODO: Implement isEmpty method
	bool result = true;
	return result;
}

template <class T>
void Vector<T>::popBack()
{
	//TODO: Implement popBack method
	int temp = 0;
}

template <class T>
void Vector<T>::pushBack(const T& value)
{
	//TODO: Expand if size matches capacity
	if (mSize < mCapacity)
	{
		new (mBuffer + mSize++) T(value);
	}
	else
	{
		throw std::exception("Attempting to push back with no available capacity. Resizing not yet implemented");
	}
}

template <class T>
void Vector<T>::reserve(int32_t capacity)
{
	//TODO: Implement reserve method
	int32_t _capacity = capacity; // Just to remove declaration warnings
}

template <class T>
void Vector<T>::clear()
{
	//TODO: Implement clear method
}

template <class T>
void Vector<T>::remove(const T& value)
{
	//TODO: Implement remove method
}

/// //////////////////////////////// ///
//  Vector Iterator implementation  ///
// //////////////////////////////// ///

template <class T>
Vector<T>::Iterator::Iterator() {}

template <class T>
Vector<T>::Iterator::Iterator(const T& value) :
	mValue(value) {}

template <class T>
Vector<T>::Iterator::Iterator(const Iterator& rhs)
{
	//TODO: Implement copy constructor
}

template <class T>
bool Vector<T>::Iterator::operator==(const Iterator& rhs)
{
	//TODO: Implement operator==()
	return true;
}

template <class T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
{
	//TODO: Implement increment operator
	return this;
}

template <class T>
T& Vector<T>::Iterator::operator*()
{
	//TODO: Implement dereference operator
	T t{};
	return t;
}

template <class T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& rhs)
{
	//TODO: Implement assignment operator
	return this;
}