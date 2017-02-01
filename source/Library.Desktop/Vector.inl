#pragma once
#include <new>
#include <cstdint>

namespace Vector
{
	template <typename T>
	Vector<T>::Vector(bool fixedSize = false) :
		mBuffer(nullptr), mSize(0), mFixedSize(fixedSize), mCapacity(CAPACITY_INCREMENT)
	{
		reserve(mCapacity);
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		clear();
		free(mBuffer);
	}

	template <typename T>
	Vector<T>::Vector(const Vector<T>& rhs) :
		Vector()
	{
		operator=(rhs);
	}

	template <typename T>
	bool Vector<T>::operator==(const Vector<T>& rhs) const
	{
		bool result = (mSize == rhs.mSize);
		try
		{
			for (std::uint32_t i = 0; i < mSize; i++)
			{
				if (operator[](i) != rhs[i])
				{
					result = false;
				}
			}
		}
		catch (const std::exception&) {}
		return result;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
	{
		if (mBuffer == nullptr) throw std::exception("Assigning to null pointer");
		clear();
		mFixedSize = rhs.mFixedSize;
		reserve(rhs.mCapacity);
		if (rhs.mSize > 0)
		{
			for (auto iter = rhs.begin(); iter != rhs.end(); ++iter)
			{
				pushBack(*iter);
			}
		}
		return *this;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::find(const T& value) const
	{
		for (Iterator iter = begin(); iter != end(); ++iter)
		{
			if (*iter == value) return iter;
		}
		return end();
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::begin() const
	{
		return Iterator::Iterator(this, 0);
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::end() const
	{
		return Iterator::Iterator(this, mSize);
	}

	template <typename T>
	T& Vector<T>::front()
	{
		if (mBuffer == nullptr || mSize == 0) throw std::exception("Calling front on a null vector");
		return *mBuffer;
	}

	template <typename T>
	const T& Vector<T>::front() const
	{
		if (mBuffer == nullptr || mSize == 0) throw std::exception("Calling front on a null vector");
		return const_cast<const T&>(*mBuffer);
	}

	template <typename T>
	T& Vector<T>::back()
	{
		if (mBuffer == nullptr || mSize == 0) throw std::exception("Calling back on null vector");
		return *(mBuffer + (mSize - 1));
	}

	template <typename T>
	const T& Vector<T>::back() const
	{
		if (mBuffer == nullptr || mSize == 0) throw std::exception("Calling back on a null vector");
		return *(mBuffer + (mSize - 1));
	}

	template <typename T>
	T& Vector<T>::at(const std::uint32_t index)
	{
		return operator[](index);
	}

	template <typename T>
	const T& Vector<T>::at(const std::uint32_t index) const
	{
		return const_cast<const T&>(operator[](index));
	}

	template <typename T>
	T& Vector<T>::operator[](const std::uint32_t index)
	{
		if (index >= mSize) throw std::exception("Index out of bounds");
		return *(mBuffer + index);
	}

	template <typename T>
	const T& Vector<T>::operator[](const std::uint32_t index) const
	{
		if (mBuffer == nullptr) throw std::exception("Buffer is null");
		if (index >= mSize) throw std::exception("Index out of bounds");
		return const_cast<const T&>(*(mBuffer + index));
	}

	template <typename T>
	void Vector<T>::popBack()
	{
		if (mBuffer == nullptr || mSize == 0) throw std::exception("Calling pop back on an empty vector");
		mBuffer[mSize-1].~T();
		--mSize;
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
		if (mSize >= mCapacity) reserve(mCapacity + CAPACITY_INCREMENT);
		new(mBuffer + mSize++) T(value);
	}

	template <typename T>
	void Vector<T>::reserve(std::uint32_t capacity)
	{
		if (capacity < mSize) capacity = mSize;
		
		T* temp = mBuffer;
		mBuffer = static_cast<T*>(malloc(sizeof(T) * capacity));
		memcpy_s(mBuffer, sizeof(T) * mSize, temp, sizeof(T) * mSize);
		
		free(temp);
		mCapacity = capacity;
	}

	template <typename T>
	void Vector<T>::clear()
	{
		while (mSize > 0)
		{
			popBack();
		}
		shrinkToFit();
	}

	template <typename T>
	void Vector<T>::remove(const T& value)
	{
		std::uint32_t firstValue = mSize;
		for (std::uint32_t i = 0; i < mSize; i++)
		{
			if (operator[](i) == value)
			{
				firstValue = i;
				break;
			}
		}

		for (std::uint32_t i = firstValue; i < mSize-1; i++)
		{
			at(i) = at(i + 1);
		}
		
		if (firstValue != mSize) --mSize;
	}

	template <class T>
	void Vector<T>::shrinkToFit()
	{
		reserve(mSize);
	}

	/// //////////////////////////////// ///
	///  Vector Iterator implementation  ///
	/// //////////////////////////////// ///
	template <typename T>
	Vector<T>::Iterator::Iterator() :
		mOwner(nullptr), mIndex(0) {}

	template <typename T>
	Vector<T>::Iterator::Iterator(const Vector<T>* owner, const std::uint32_t index) :
		mOwner(owner), mIndex(index) {}

	template <typename T>
	Vector<T>::Iterator::Iterator(const Iterator& rhs) :
		mOwner(rhs.mOwner), mIndex(rhs.mIndex) {}

	template <typename T>
	bool Vector<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return mOwner == rhs.mOwner && mIndex == rhs.mIndex;
	}

	template <typename T>
	bool Vector<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		mIndex++;
		if (mIndex > mOwner->size()) throw std::exception("Incrementing beyond vector bounds");
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
	T& Vector<T>::Iterator::operator*() const
	{
		if (mOwner == nullptr) throw std::exception("Owner is null");
		if (mIndex > mOwner->size()) throw std::exception("Vector out of bounds");
		return const_cast<T&>(mOwner->operator[](mIndex));
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& rhs)
	{
		mOwner = rhs.mOwner;
		mIndex = rhs.mIndex;
		return *this;
	}
}
