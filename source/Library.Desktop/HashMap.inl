#pragma once
#include <cstdint>
#include "Vector.h"

namespace Library
{
	template <typename TKey, typename TValue, typename HashFunctor>
	HashMap<TKey, TValue, HashFunctor>::HashMap(std::uint32_t bucketCount = defaultBucketCount):
		mBucketCount(bucketCount), mBuckets(), mSize(0)
	{
		if (mBucketCount == 0) throw std::exception("HashMap constructed with an invalid amount of buckets");
		initializeBuckets();
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	HashMap<TKey, TValue, HashFunctor>::HashMap(const HashMap<TKey, TValue, HashFunctor>& rhs):
		mBucketCount(rhs.mBucketCount), mSize(rhs.mSize)
	{
		if (this == &rhs) throw std::exception("Self assignment error");

		initializeBuckets();
		mSize = rhs.mSize;
		for (std::uint32_t i = 0; i < mBucketCount; i++)
		{
			mBuckets[i] = rhs.mBuckets[i];
		}
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	HashMap<TKey, TValue, HashFunctor>& 
		HashMap<TKey, TValue, HashFunctor>::operator=(const HashMap<TKey, TValue, HashFunctor>& rhs)
	{
		if (this == &rhs) throw std::exception("Self assignment error");

		mBucketCount = rhs.mBucketCount;
		mHashFunctor = rhs.mHashFunctor;
		initializeBuckets();
		for (std::uint32_t i = 0; i < mBucketCount; i++)
		{
			mBuckets[i] = rhs.mBuckets[i];
		}
		mSize = rhs.mSize;
		return *this;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	void HashMap<TKey, TValue, HashFunctor>::initializeBuckets()
	{
		mSize = 0;
		for (std::uint32_t i = 0; i < mBucketCount; i++)
		{ // Create a vector to represent each "bucket:
			mBuckets.pushBack(BucketType());
		}
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::find(const TKey& key) const
	{
		if (mBuckets.isEmpty()) throw std::exception("Buckets are null");
		std::uint32_t hashIndex = mHashFunctor(key) % mBucketCount;
		
		Iterator iter;
		auto vIter = mBuckets[hashIndex].begin();
		
		// Iterate until matching key is found or end of bucket is hit
		while (vIter != mBuckets[hashIndex].end())
		{
			if ((*vIter).first == key) break;
			++vIter;
		}

		// If we are at the end of the bucket, return the end of the HashMap
		if (vIter == mBuckets[hashIndex].end())
		{
			hashIndex = mBucketCount - 1;
			vIter = mBuckets[hashIndex++].end();
		}

		return Iterator(this, hashIndex, vIter);
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::insert(const PairType& entry)
	{
		// Determine which bucket the data will be put into
		std::uint32_t bucketIndex = mHashFunctor(entry.first) % mBucketCount;
		
		// Push the data onto the appropriate bucket
		mBuckets[bucketIndex].pushBack(entry);
		mSize++;
		
		// Return an iterator pointing to the entry
		return HashMap<TKey, TValue>::Iterator(this, bucketIndex, mBuckets[bucketIndex].find(entry));
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	void HashMap<TKey,TValue, HashFunctor>::remove(const TKey& key)
	{
		auto iter = find(key);
		if (iter != end())
		{
			std::uint32_t hashIndex = mHashFunctor(key) % mBucketCount;
			mBuckets[hashIndex].remove(*iter);
			mSize--;
		}
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	TValue& HashMap<TKey, TValue, HashFunctor>::operator[](const TKey& key)
	{
		auto iter = find(key);
		
		if (iter == end())
		{
			PairType newPair(key, TValue());
			iter = insert(newPair);
		}
		
		return iter->second;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	const TValue& HashMap<TKey, TValue, HashFunctor>::operator[](const TKey& key) const
	{
		auto iter = find(key);

		if (iter == end()) throw std::exception("Attempting to call insert on a const HashMap");

		return iter->second;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::begin() const
	{
		Iterator result = end();

		if (mSize > 0)
		{
			std::uint32_t index = 0;
			auto iter = mBuckets[index].begin();
			while (iter == mBuckets[index].end() && index + 1 < mBucketCount)
			{
				iter = mBuckets[++index].begin();
			}
			result = Iterator(this, index, iter);
		}

		return result;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::end() const
	{
		return Iterator(this, mBucketCount, mBuckets[mBucketCount - 1].end());
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	void HashMap<TKey, TValue, HashFunctor>::clear()
	{
		for (std::uint32_t i = 0; i < mBucketCount; i++)
		{
			mBuckets[i].clear();
		}
		initializeBuckets();
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	std::uint32_t HashMap<TKey, TValue, HashFunctor>::size() const
	{
		return mSize;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	bool HashMap<TKey, TValue, HashFunctor>::containsKey(const TKey& key) const
	{
		auto iter = find(key);
		return iter != end();
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator():
		mOwner(nullptr), mBucketIndex(0), mIter(Library::Vector<PairType>::Iterator()) {}

	template <typename TKey, typename TValue, typename HashFunctor>
	HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator(const Iterator& rhs) :
		mOwner(rhs.mOwner), mBucketIndex(rhs.mBucketIndex), mIter(rhs.mIter) {}

	template <typename TKey, typename TValue, typename HashFunctor>
	HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator(const HashMap<TKey, TValue, HashFunctor>* owner, std::uint32_t bucketIndex, typename Library::Vector<PairType>::Iterator iter) :
		mOwner(owner), mBucketIndex(bucketIndex), mIter(iter) {}

	template <typename TKey, typename TValue, typename HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::Iterator& HashMap<TKey, TValue, HashFunctor>::Iterator::operator=(const Iterator& rhs)
	{
		if (rhs.mOwner == nullptr) throw std::exception("Right hand side owner is null");
		mOwner = rhs.mOwner;
		mBucketIndex = rhs.mBucketIndex;
		mIter = rhs.mIter;
		return *this;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::Iterator& HashMap<TKey, TValue, HashFunctor>::Iterator::operator++()
	{
		if (mOwner == nullptr) throw std::exception("Incrementing beyond HashMap bounds");
		
		++mIter;
		while (mIter == mOwner->mBuckets[mBucketIndex].end())
		{
			if (++mBucketIndex< mOwner->mBucketCount)
			{
				mIter = mOwner->mBuckets[mBucketIndex].begin();
			}
			else break;
		}
	
		return *this;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::Iterator::operator++(int)
	{
		auto copy = *this;
		operator++();
		return copy;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::PairType& HashMap<TKey, TValue, HashFunctor>::Iterator::operator*()
	{
		if (mOwner == nullptr) throw std::exception("Attempting to dereference null iterator");
		return (*mIter);
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	const typename HashMap<TKey, TValue, HashFunctor>::PairType& HashMap<TKey, TValue, HashFunctor>::Iterator::operator*() const
	{
		if (mOwner == nullptr) throw std::exception("Attempting to dereference null iterator");
		return (*mIter);
	}

	template <typename TKey, typename TValue, class HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::PairType* HashMap<TKey, TValue, HashFunctor>::Iterator::operator->()
	{
		return &(operator*());
	}

	template <typename TKey, typename TValue, class HashFunctor>
	const typename HashMap<TKey, TValue, HashFunctor>::PairType* HashMap<TKey, TValue, HashFunctor>::Iterator::operator->() const
	{
		return &(operator*());
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	bool HashMap<TKey, TValue, HashFunctor>::Iterator::operator==(const Iterator& rhs) const
	{
		if (mOwner == nullptr) throw std::exception("Owner is null");

		return mOwner == rhs.mOwner &&
			mBucketIndex == rhs.mBucketIndex &&
			mIter == rhs.mIter;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	bool HashMap<TKey, TValue, HashFunctor>::Iterator::operator!=(const Iterator& rhs) const
	{
		if (mOwner == nullptr) throw std::exception("Owner is null");
		return !(operator==(rhs));
	}
}
