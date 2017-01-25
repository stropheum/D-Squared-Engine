#pragma once
#include <new>
#include <cstdint>

template <typename T>
Vector<T>::Vector() :
	mBuffer(nullptr), mSize(0), mCapacity(10)
{
	reserve(mCapacity);
}

template <typename T>
Vector<T>::~Vector()
{
	clear();
}

template <typename T>
Vector<T>::Vector(const Vector<T>& rhs) :
	mBuffer(nullptr), mSize(0), mCapacity(0)
{
	this->operator=(rhs);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
	reserve(rhs.mCapacity);
	memcpy(mBuffer, rhs.mBuffer, rhs.size());
	mSize = rhs.mSize;
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& rhs)
{
	reserve(rhs.mCapacity);
	memcpy(mBuffer, rhs.mBuffer, rhs.size());
	mSize = rhs.mSize;
	return *this;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::find(const T& value)
{
	uint32_t index = mSize;
	for (std::uint32_t i = 0; i < mSize; i++)
	{
		if ((*mBuffer + i) == value)
		{
			index = i;
			break;
		}
	}
	return Iterator(index);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin()
{
	return Iterator(this, 0);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end()
{
	return Iterator(this, mSize);
}

template <typename T>
T& Vector<T>::front()
{
	if (mBuffer == nullptr) throw std::exception("Calling front on null vector");
	return *mBuffer;
}

template <typename T>
T& Vector<T>::back()
{
	if (mBuffer == nullptr) throw std::exception("Calling back on null vector");
	return *(mBuffer + (mSize - 1));
}

template <typename T>
T& Vector<T>::at(const std::uint32_t index)
{
	return operator[](index);
}

template <typename T>
T& Vector<T>::operator[](const std::uint32_t index)
{
	if (index >= mSize) throw std::exception("Index out of bounds");
	return *(mBuffer + index);
}

template <typename T>
T Vector<T>::popBack()
{
	return *(mBuffer + --mSize);
}

template <typename T>
std::uint32_t Vector<T>::size() const
{
	return mSize;
}

template <typename T>
std::uint32_t Vector<T>::capacity() const
{
	return mCapacity;
}

template <typename T>
bool Vector<T>::isEmpty() const
{
	return mSize == 0;
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
void Vector<T>::reserve(std::uint32_t capacity)
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
	for (std::uint32_t i = 0; i < mSize; i++)
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
Vector<T>::Iterator::Iterator() :
	mOwner(this), mIndex(0) {}

template <typename T>
Vector<T>::Iterator::Iterator(const std::uint32_t index) :
	mOwner(this) , mIndex(index) {}

template <typename T>
Vector<T>::Iterator::Iterator(const Iterator& rhs) :
	mOwner(rhs.mOwner), mIndex(rhs.mIndex) {}

template <typename T>
bool Vector<T>::Iterator::operator==(const Iterator& rhs)
{
	return mOwner == rhs.mOwner && mIndex == rhs.mIndex;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
{
	mIndex++;
	if (mIndex > mOwner->size()) throw std::exception("Increminting beyond vector bounds");
	return *this;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
{
	Iterator result(mIndex);
	operator++();
	return result;
}

template <typename T>
T& Vector<T>::Iterator::operator*()
{
	if (mIndex > mOwner->size()) throw std::exception("Vector out of bounds");
	return mOwner->at(mIndex);
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& rhs)
{
	mOwner = rhs.mOwner;
	mIndex = rhs.mIndex;
	return *this;
}