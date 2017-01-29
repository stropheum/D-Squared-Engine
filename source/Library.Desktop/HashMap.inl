#pragma once
#include <cstdint>
#include <functional>
#include "Vector.h"

namespace HashMap
{
#define HashMapTemplate typename TKey, typename TData

	template <HashMapTemplate>
	HashMap<TKey, TData>::HashMap(
		std::uint32_t hashMapSize, std::function<std::uint32_t(TKey, std::uint32_t)> hashFunctor=defaultHashFunctor) :
		mHashMapSize(hashMapSize), mHashFunctor(hashFunctor)
	{
		for (std::uint32_t i = 0; i < hashMapSize; i++)
		{ // Create a Vector to represent each "bucket"
			mBuckets.pushBack(Vector::Vector<TData>());
		}
	}

	template <HashMapTemplate>
	HashMap<TKey, TData>::~HashMap()
	{
		//TODO: Implement destructor
	}

	template <HashMapTemplate>
	HashMap<TKey, TData>::HashMap(const HashMap<TKey, TData>& rhs)
	{
		//TODO: Implement copy constructor
	}

	template <HashMapTemplate>
	HashMap<TKey, TData>& HashMap<TKey, TData>::operator=(const HashMap<TKey, TData>& rhs)
	{
		//TODO: Implement assignment operator
		return *this;
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

	template <HashMapTemplate>
	TData& HashMap<TKey, TData>::operator[](const TKey& key)
	{
		//TODO: Implement index of operator
	}

	template <class TKey, class TData>
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

	template <HashMapTemplate>
	HashMap<TKey, TData>::Iterator::Iterator(const HashMap<TKey, TData>* owner, const TKey& key, const TData& data) :
		mOwner(owner), mPair(key, data) {}
}
