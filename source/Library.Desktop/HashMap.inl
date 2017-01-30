#pragma once
#include <cstdint>
#include <functional>
#include "Vector.h"

namespace HashMap
{
#define HashMapTemplate typename TKey, typename TData

	template <HashMapTemplate>
	HashMap<TKey, TData>::HashMap():
		mHashMapSize(defaultHashMapSize), mHashFunctor(defaultHashFunctor)
	{
		initializeBuckets();
	}

	template <HashMapTemplate>
	HashMap<TKey, TData>::HashMap(
		std::uint32_t hashMapSize=defaultHashMapSize, 
		std::function<std::uint32_t(TKey, std::uint32_t)> hashFunctor=defaultHashFunctor):
		mHashMapSize(hashMapSize), mHashFunctor(hashFunctor)
	{
		initializeBuckets();
	}

	template <HashMapTemplate>
	HashMap<TKey, TData>::~HashMap()
	{
		//TODO: Implement destructor
	}

	template <HashMapTemplate>
	HashMap<TKey, TData>::HashMap(const HashMap<TKey, TData>& rhs): 
		mHashMapSize(rhs.mHashMapSize), mHashFunctor(rhs.mHashFunctor) {
		//TODO: Implement copy constructor
	}

	template <HashMapTemplate>
	HashMap<TKey, TData>& HashMap<TKey, TData>::operator=(const HashMap<TKey, TData>& rhs)
	{
		//TODO: Implement assignment operator
		return *this;
	}

	template <class TKey, class TData>
	void HashMap<TKey, TData>::initializeBuckets()
	{
		for (std::uint32_t i = 0; i < mHashMapSize; i++)
		{ // Create a vector to represent each "bucket:
			mBuckets.pushBack(BucketType());
		}
	}

	//	template <HashMapTemplate>
//	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::find(const TKey& key) const
//	{
//		//TODO: Implement find method
//	}

	//TODO: Remove this method and replace it with the one that returns an iterator
	template <HashMapTemplate>
	void HashMap<TKey, TData>::find(const TKey& key) const
	{
		std::uint32_t result = mHashFunctor(key, mHashMapSize);
		auto temp = result;
		if (result == 2 && temp == 0)
		{
			// do things
		}
	}

	template <class TKey, class TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::insert(const PairType& entry)
	{
		// Determine which bucket the data will be put into
		std::uint32_t bucketIndex = mHashFunctor(entry.first, mHashMapSize);
		
		// Push the data onto the appropriate bucket
		mBuckets[bucketIndex].pushBack(entry.second);
		
		// Return an iterator pointing to the entry
		return Iterator(this, entry);
	}


	template <HashMapTemplate>
	TData& HashMap<TKey, TData>::operator[](const TKey& key)
	{
		auto bucket = mBuckets[mHashFunctor(key, mHashMapSize)];
		for (PairType value : bucket)
		{
			if (value->first == key)
			{
				return value->second;
			}
		}
		throw std::exception("Accessing non-existent HashMap key");
	}

	template <HashMapTemplate>
	void HashMap<TKey, TData>::clear()
	{
		for (std::uint32_t i = 0; i < mHashMapSize; i++)
		{
			mBuckets[i].~Vector();
		}
	}

	template <HashMapTemplate>
	std::uint32_t HashMap<TKey, TData>::defaultHashFunctor(const TKey& key, const std::uint32_t& hashMapSize)
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
		return sum % hashMapSize;
	}

	template <class TKey, class TData>
	HashMap<TKey, TData>::Iterator::Iterator():
		mOwner(nullptr), mPair(nullptr) {}

	template <HashMapTemplate>
	HashMap<TKey, TData>::Iterator::Iterator(const HashMap<TKey, TData>* owner, const PairType& pair) :
		mOwner(owner), mPair(pair) {}
}
