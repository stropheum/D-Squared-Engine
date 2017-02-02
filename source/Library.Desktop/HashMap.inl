#pragma once
#include <cstdint>
#include <functional>
#include "Vector.h"

namespace HashMap
{
#define HashMapTemplate typename TKey, typename TValue

	template <class TKey, class TValue>
	HashMap<TKey, TValue>::HashMap(std::function<std::uint32_t(const TKey&)> hashFunctor = defaultHashFunctor):
		mHashMapSize(defaultHashMapSize), mHashFunctor(hashFunctor)
	{
		initializeBuckets();
	}

	template <typename TKey, typename TValue>
	HashMap<TKey, TValue>::HashMap(
		std::uint32_t hashMapSize=defaultHashMapSize, 
		std::function<std::uint32_t(const TKey&)> hashFunctor = defaultHashFunctor):
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

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::Iterator HashMap<TKey, TValue>::find(const TKey& key) const
	{
		if (mBuckets.isEmpty()) throw std::exception("Buckets are null");
		Iterator iter;
		for (iter = begin(); iter != end(); ++iter)
		{
			if ((*iter).first == key) break;
		}
		return iter;
	}

	template <class TKey, class TValue>
	typename HashMap<TKey, TValue>::Iterator HashMap<TKey, TValue>::insert(const PairType& entry)
	{
		// Determine which bucket the data will be put into
		std::uint32_t bucketIndex = mHashFunctor(entry.first) % mHashMapSize;
		
		// Push the data onto the appropriate bucket
		mBuckets[bucketIndex].pushBack(entry);
		
		// Return an iterator pointing to the entry
		return HashMap<TKey, TValue>::Iterator(this, bucketIndex, mBuckets[bucketIndex].find(entry));
	}


	template <typename TKey, typename TValue>
	TValue& HashMap<TKey, TValue>::operator[](const TKey& key)
	{
		auto bucket = mBuckets[mHashFunctor(key, mHashMapSize) % mHashMapSize];
		for (PairType value : bucket)
		{
			if (value->first == key)
			{
				return value->second;
			}
		}
		PairType newPair(key, nullptr);
		return *(insert(newPair)).second;
	}

	template <class TKey, class TValue>
	typename HashMap<TKey, TValue>::Iterator HashMap<TKey, TValue>::begin() const
	{
		std::uint32_t index = 0;
		auto iter = mBuckets[index].begin();
		while (iter == mBuckets[index].end() && index + 1 < mHashMapSize)
		{
			iter = mBuckets[++index].begin();
		}
		return Iterator(this, index, iter);
	}

	template <class TKey, class TValue>
	typename HashMap<TKey, TValue>::Iterator HashMap<TKey, TValue>::end() const
	{
		return Iterator(this, mHashMapSize, mBuckets[mHashMapSize - 1].end());
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
		const std::int8_t* bytes = reinterpret_cast<const std::int8_t*>(&key);
		
		// Iterate over the array of bytes, building an integer
		std::uint32_t hash = 0;
		for (std::uint32_t i = 0; i < strlen(reinterpret_cast<const char*>(bytes)); i++)
		{
			hash += bytes[i];
		}

		// Mod the summed byte array value by the size of the hash map to get the bucket index
		return hash;
	}

	template <typename TKey, typename TValue>
	HashMap<TKey, TValue>::Iterator::Iterator():
		mOwner(nullptr), mBucketIndex(0), mIter(Vector::Vector<PairType>::Iterator()) {}

	template <class TKey, class TValue>
	HashMap<TKey, TValue>::Iterator::Iterator(const Iterator& rhs) :
		mOwner(rhs.mOwner), mBucketIndex(rhs.mBucketIndex), mIter(rhs.mIter) {}

	template <typename TKey, typename TValue>
	HashMap<TKey, TValue>::Iterator::Iterator(const HashMap<TKey, TValue>* owner, std::uint32_t bucketIndex, typename Vector::Vector<PairType>::Iterator iter) :
		mOwner(owner), mBucketIndex(bucketIndex), mIter(iter) {}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::Iterator& HashMap<TKey, TValue>::Iterator::operator=(const Iterator& rhs)
	{
		if (rhs.mOwner == nullptr) throw std::exception("Rhs owner is null");
		mOwner = rhs.mOwner;
		mBucketIndex = rhs.mBucketIndex;
		mIter = rhs.mIter;
		return *this;
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::Iterator& HashMap<TKey, TValue>::Iterator::operator++()
	{
		if (mOwner == nullptr) throw std::exception("Incrementing beyond HashMap bounds");
		
		++mIter;
		while (mIter == mOwner->mBuckets[mBucketIndex].end())
		{
			if (++mBucketIndex< mOwner->mHashMapSize)
			{
				mIter = mOwner->mBuckets[mBucketIndex].begin();
			}
			else break;
		}
	
		return *this;
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::Iterator HashMap<TKey, TValue>::Iterator::operator++(int)
	{
		auto copy = *this;
		operator++();
		return copy;
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::PairType& HashMap<TKey, TValue>::Iterator::operator*() const
	{
		if (mOwner == nullptr) throw std::exception("Attempting to dereference null iterator");
		return (*mIter);
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::PairType& HashMap<TKey, TValue>::Iterator::operator->() const
	{
		if (mOwner == nullptr) throw std::exception("Attempting to dereference null iterator");
		return (*mIter);
	}

	template <typename TKey, typename TValue>
	bool HashMap<TKey, TValue>::Iterator::operator==(const Iterator& rhs) const
	{
		if (mOwner == nullptr) throw std::exception("Owner is null");

		return mOwner == rhs.mOwner &&
			mBucketIndex == rhs.mBucketIndex &&
			mIter == rhs.mIter;
	}

	template <typename TKey, typename TValue>
	bool HashMap<TKey, TValue>::Iterator::operator!=(const Iterator& rhs) const
	{
		if (mOwner == nullptr) throw std::exception("Owner is null");
		return !(operator==(rhs));
	}
}
