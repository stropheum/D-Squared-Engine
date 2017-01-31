#pragma once
#include <cstdint>
#include <functional>
#include "Vector.h"

namespace HashMap
{
#define HashMapTemplate typename TKey, typename TData

	template <typename TKey, typename TValue>
	HashMap<TKey, TValue>::HashMap():
		mHashMapSize(defaultHashMapSize), mHashFunctor(defaultHashFunctor), mBuckets(mHashMapSize)
	{
		initializeBuckets();
	}

	template <typename TKey, typename TValue>
	HashMap<TKey, TValue>::HashMap(
		std::uint32_t hashMapSize=defaultHashMapSize, 
		std::function<std::uint32_t(TKey)> hashFunctor=defaultHashFunctor):
		mHashMapSize(hashMapSize), mHashFunctor(hashFunctor)
	{
		initializeBuckets();
	}

	template <typename TKey, typename TValue>
	HashMap<TKey, TValue>::~HashMap()
	{
		//TODO: Implement destructor
	}

	template <typename TKey, typename TValue>
	HashMap<TKey, TValue>::HashMap(const HashMap<TKey, TValue>& rhs): 
		mHashMapSize(rhs.mHashMapSize), mHashFunctor(rhs.mHashFunctor) {
		//TODO: Implement copy constructor
	}

	template <typename TKey, typename TValue>
	HashMap<TKey, TValue>& HashMap<TKey, TValue>::operator=(const HashMap<TKey, TValue>& rhs)
	{
		//TODO: Implement assignment operator
		return *this;
	}

	template <class TKey, class TValue>
	void HashMap<TKey, TValue>::initializeBuckets()
	{
		for (std::uint32_t i = 0; i < mHashMapSize; i++)
		{ // Create a vector to represent each "bucket:
			mBuckets.pushBack(BucketType());
		}
	}

//	template <typename TKey, typename TData>
//	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::find(const TKey& key) const
//	{
//		//TODO: Implement find method
//	}

	//TODO: Remove this method and replace it with the one that returns an iterator
	template <typename TKey, typename TValue>
	void HashMap<TKey, TValue>::find(const TKey& key) const
	{
		std::uint32_t result = mHashFunctor(key);
		auto temp = result;
		if (result == 2 && temp == 0)
		{
			// do things
		}
	}

	template <class TKey, class TValue>
	typename HashMap<TKey, TValue>::Iterator HashMap<TKey, TValue>::insert(const PairType& entry)
	{
		// Determine which bucket the data will be put into
		std::uint32_t bucketIndex = mHashFunctor(entry.first, mHashMapSize);
		
		// Push the data onto the appropriate bucket
		mBuckets[bucketIndex].pushBack(entry.second);
		
		// Return an iterator pointing to the entry
		return Iterator(this, entry);
	}


	template <typename TKey, typename TValue>
	TValue& HashMap<TKey, TValue>::operator[](const TKey& key)
	{
		auto bucket = mBuckets[mHashFunctor(key, mHashMapSize) & mHashMapSize];
		for (PairType value : bucket)
		{
			if (value->first == key)
			{
				return value->second;
			}
		}
		throw std::exception("Accessing non-existent HashMap key");
	}

	template <typename TKey, typename TValue>
	void HashMap<TKey, TValue>::clear()
	{
		for (std::uint32_t i = 0; i < mHashMapSize; i++)
		{
			mBuckets[i].~Vector();
		}
	}

	template <typename TKey, typename TValue>
	std::uint32_t HashMap<TKey, TValue>::defaultHashFunctor(const TKey& key)
	{
		// Convert the key to an array of bytes
		auto bytes = reinterpret_cast<const char*>(key);
		std::uint32_t sum = 0;

		// Iterate over the array of bytes, building an integer
		for (std::uint32_t i = 0; i < sizeof(key); i++)
		{
			sum += bytes[i];
		}

		// Mod the summed byte array value by the size of the hash map to get the bucket index
		return sum;
	}

	template <typename TKey, typename TValue>
	HashMap<TKey, TValue>::Iterator::Iterator():
		mOwner(nullptr), mBucketIndex(0), mIter(mBuckets[0].begin()) {}

	template <typename TKey, typename TValue>
	HashMap<TKey, TValue>::Iterator::Iterator(const HashMap<TKey, TValue>* owner, typename Vector::Vector<PairType>::Iterator iter) :
		mOwner(owner), mBucketIndex(0), mIter(iter) {}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::Iterator& HashMap<TKey, TValue>::Iterator::operator++()
	{
		if (mOwner == nullptr) throw std::exception("Incrementing beyond HashMap bounds");

		++mIter;
		while (mIter == mBuckets[mBucketIndex].end())
		{
			if (mBucketIndex + 1 < mOwner->mHashMapSize)
			{
				++mBucketIndex;
				mIter = mBuckets[mBucketIndex].begin();
			}
			else break;
		}
		return *this;
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::Iterator HashMap<TKey, TValue>::Iterator::begin()
	{
		return Iterator(this, mBuckets[0].begin());
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::Iterator HashMap<TKey, TValue>::Iterator::end()
	{
		return Iterator(this, mBuckets[mOwner->mHashMapSize - 1].end());
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::Iterator HashMap<TKey, TValue>::Iterator::operator++(int)
	{
		auto copy = *this;
		operator++();
		return copy;
	}
}
