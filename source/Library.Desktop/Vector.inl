#pragma once
#include <new>
#include <cstdint>

namespace Library
{
	template <typename T>
	Vector<T>::Vector(bool fixedSize) :
		mBuffer(nullptr), mSize(0), mCapacity(CAPACITY_INCREMENT), mFixedSize(fixedSize)
	{
		Reserve(mCapacity);
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		Clear();
		free(mBuffer);
	}

	template <typename T>
	Vector<T>::Vector(const Vector<T>& rhs):
		mBuffer(nullptr), mSize(0), mCapacity(rhs.mCapacity), mFixedSize(rhs.mFixedSize)
	{
		operator=(rhs);
	}

	template <class T>
	Vector<T>::Vector(Vector<T>&& rhs) noexcept
	{
		operator=(std::move(rhs));
	}

	template <class T>
	Vector<T>& Vector<T>::operator=(Vector<T>&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();

			mBuffer = rhs.mBuffer;
			mSize = rhs.mSize;
			mCapacity = rhs.mCapacity;
			mFixedSize = rhs.mFixedSize;

			rhs.mBuffer = nullptr;
			rhs.mSize = 0;
			rhs.mCapacity = 0;
		}
		
		return *this;
	}

	template <typename T>
	bool Vector<T>::operator==(const Vector<T>& rhs) const
	{
		bool result = (mSize == rhs.mSize);
		
		if (result)
		{ // If sizes are equal, compare further
			for (std::uint32_t i = 0; i < mSize; i++)
			{
				if (operator[](i) != rhs[i])
				{
					result = false;
				}
			}
		}

		return result;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
	{
		if (this != &rhs)
		{
			mFixedSize = rhs.mFixedSize;

			Clear();
			Reserve(rhs.mCapacity);
			if (rhs.mSize > 0)
			{
				for (auto iter = rhs.begin(); iter != rhs.end(); ++iter)
				{
					PushBack(*iter);
				}
			}
		}
		return *this;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& value) const
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
	T& Vector<T>::Front()
	{
		if (mSize == 0) throw std::exception("Calling Front on a null vector");
		return *mBuffer;
	}

	template <typename T>
	const T& Vector<T>::Front() const
	{
		if (mSize == 0) throw std::exception("Calling Front on a null vector");
		return const_cast<const T&>(*mBuffer);
	}

	template <typename T>
	T& Vector<T>::Back()
	{
		if (mSize == 0) throw std::exception("Calling Back on null vector");
		return *(mBuffer + (mSize - 1));
	}

	template <typename T>
	const T& Vector<T>::Back() const
	{
		if (mSize == 0) throw std::exception("Calling Back on a null vector");
		return *(mBuffer + (mSize - 1));
	}

	template <typename T>
	T& Vector<T>::At(const std::uint32_t& index)
	{
		return operator[](index);
	}

	template <typename T>
	const T& Vector<T>::At(const std::uint32_t& index) const
	{
		return const_cast<const T&>(operator[](index));
	}

	template <typename T>
	T& Vector<T>::operator[](const std::uint32_t& index)
	{
		if (index >= mSize) throw std::exception("Index out of bounds");
		return *(mBuffer + index);
	}

	template <typename T>
	const T& Vector<T>::operator[](const std::uint32_t& index) const
	{
		if (mBuffer == nullptr) throw std::exception("Buffer is null");
		if (index >= mSize) throw std::exception("Index out of bounds");
		return const_cast<const T&>(*(mBuffer + index));
	}

	template <typename T>
	void Vector<T>::PopBack()
	{
		if (mBuffer == nullptr || mSize == 0) throw std::exception("Calling pop Back on an empty vector");
		mBuffer[mSize-1].~T();
		--mSize;
	}

	template <typename T>
	std::uint32_t Vector<T>::Size() const
	{
		return mSize;
	}

	template <typename T>
	std::uint32_t Vector<T>::Capacity() const
	{
		return mCapacity;
	}

	template <typename T>
	bool Vector<T>::IsEmpty() const
	{
		return mSize == 0;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::PushBack(const T& value)
	{
		typename Vector<T>::Iterator iter = end();
		if (!mFixedSize)
		{
			if (mSize >= mCapacity) Reserve(mCapacity + CAPACITY_INCREMENT);
			new(mBuffer + mSize++) T(value);
			iter = Iterator(this, mSize - 1); // Reassign iter to point to last value pushed Back
		}
		return iter;
	}

	template <typename T>
	void Vector<T>::Reserve(std::uint32_t capacity)
	{
		if (capacity < mSize) capacity = mSize;
		
		T* temp = mBuffer;
		mBuffer = static_cast<T*>(malloc(sizeof(T) * capacity));
		if (mSize > 0) memcpy(mBuffer, temp, sizeof(T) * mSize);

		free(temp);
		mCapacity = capacity;
	}

	template <typename T>
	void Vector<T>::Clear()
	{
		if (!IsEmpty())
		{
			while (mSize > 0)
			{
				PopBack();
			}
		}
		ShrinkToFit();
	}

	template <typename T>
	void Vector<T>::Remove(const T& value)
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

		// Destruct the value that we're about to squish
		if (firstValue != mSize) mBuffer[firstValue].~T();

		// Shift the entire buffer after the removed value down by 1 and decrement Size
		auto sizeToMove = (mCapacity * sizeof(T)) - (firstValue * sizeof(T));
		memmove(mBuffer + firstValue, mBuffer + firstValue + 1, sizeToMove);
		
		if (firstValue != mSize) --mSize;
	}

	template <class T>
	void Vector<T>::ShrinkToFit()
	{
		if (!mFixedSize) Reserve(mSize);
	}


	template <typename T>
	Vector<T>::Iterator::Iterator() :
		mOwner(nullptr), mIndex(0) {}

	template <typename T>
	Vector<T>::Iterator::Iterator(const Vector<T>* owner, const std::uint32_t& index) :
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
		if (mOwner == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (mIndex > mOwner->Size()) throw std::exception("Incrementing beyond vector bounds");
		if (mIndex < mOwner->mSize)
		{
			mIndex++;
		}

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
		if (mOwner == nullptr) throw std::exception("Owner is null");
		if (mIndex > mOwner->Size()) throw std::exception("Vector out of bounds");
		return const_cast<T&>(mOwner->operator[](mIndex));
	}

	template <typename T>
	const T& Vector<T>::Iterator::operator*() const
	{
		if (mOwner == nullptr) throw std::exception("Owner is null");
		if (mIndex > mOwner->Size()) throw std::exception("Vector out of bounds");
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
