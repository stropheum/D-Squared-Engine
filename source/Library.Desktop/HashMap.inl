#pragma once
#include <cstdint>
#include "Vector.h"

namespace Library
{
	template <typename TKey, typename TValue, typename HashFunctor>
	HashMap<TKey, TValue, HashFunctor>::HashMap(std::uint32_t bucketCount) :
		mBucketCount(bucketCount), mBuckets(), mSize(0)
	{	// HashMaps need to be constructed with At least one bucket, or nothing will be able to be stored
		if (mBucketCount == 0) { throw std::exception("HashMap constructed with an invalid amount of buckets"); }
		InitializeBuckets();
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	HashMap<TKey, TValue, HashFunctor>::HashMap(const HashMap<TKey, TValue, HashFunctor>& rhs) :
		mBucketCount(rhs.mBucketCount), mBuckets(rhs.mBuckets), mSize(rhs.mSize)
	{}

	template <typename TKey, typename TValue, typename HashFunctor>
	HashMap<TKey, TValue, HashFunctor>&
		HashMap<TKey, TValue, HashFunctor>::operator=(const HashMap<TKey, TValue, HashFunctor>& rhs)
	{
		if (this != &rhs)
		{
			mBucketCount = rhs.mBucketCount;
			mBuckets = rhs.mBuckets;
			mSize = rhs.mSize;
			mHashFunctor = rhs.mHashFunctor;
		}
		return *this;
	}

	template <typename TKey, typename TValue, class HashFunctor>
	HashMap<TKey, TValue, HashFunctor>::HashMap(HashMap<TKey, TValue, HashFunctor>&& rhs) noexcept :
		mBucketCount(0), mHashFunctor(), mBuckets(), mSize(0)
	{
		operator=(std::move(rhs));
	}

	template <typename TKey, typename TValue, class HashFunctor>
	HashMap<TKey, TValue, HashFunctor>& HashMap<TKey, TValue, HashFunctor>::operator=(HashMap<TKey, TValue, HashFunctor>&& rhs)
	{
		mBuckets = std::move(rhs.mBuckets);
		mSize = rhs.mSize;
		mBucketCount = rhs.mBucketCount;
		mHashFunctor = rhs.mHashFunctor;

		rhs.mBuckets.Clear();
		rhs.mSize = 0;
		rhs.mBucketCount = 0;

		return *this;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	void HashMap<TKey, TValue, HashFunctor>::InitializeBuckets()
	{
		mSize = 0;
		for (std::uint32_t i = 0; i < mBucketCount; i++)
		{	// Create a vector to represent each "bucket:
			mBuckets.PushBack(BucketType());
		}
		mBuckets.ShrinkToFit();
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::Find(const TKey& key) const
	{
		if (mBuckets.IsEmpty()) throw std::exception("Buckets are null");
		std::uint32_t hashIndex = mHashFunctor(key) % mBucketCount;
		auto& bucket = mBuckets[hashIndex];

		typename Vector<PairType>::Iterator iter;
		for (iter = bucket.begin(); iter != bucket.end(); ++iter)
		{
			if ((*iter).first == key) break;
		}

		typename HashMap<TKey, TValue, HashFunctor>::Iterator result;
		if (iter == bucket.end())
		{
			result = end();
		}
		else
		{
			result = HashMap<TKey, TValue, HashFunctor>::Iterator(this, hashIndex, iter);
		}

		return result;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::Insert(const PairType& entry)
	{
		auto iter = Find(entry.first);

		if (iter == end())
		{
			mSize++;
			std::uint32_t bucketIndex = mHashFunctor(entry.first) % mBucketCount;
			auto vIter = mBuckets[bucketIndex].PushBack(entry);
			iter = HashMap<TKey, TValue>::Iterator(this, bucketIndex, vIter);
		}

		return iter;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::Insert(const PairType& entry, bool& found)
	{
		auto iter = Find(entry.first);

		if (iter == end())
		{
			found = false;
			mSize++;
			std::uint32_t bucketIndex = mHashFunctor(entry.first) % mBucketCount;
			auto vIter = mBuckets[bucketIndex].PushBack(entry);
			iter = HashMap<TKey, TValue>::Iterator(this, bucketIndex, vIter);
		}
		else
		{
			found = true;
		}

		return iter;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	void HashMap<TKey,TValue, HashFunctor>::Remove(const TKey& key)
	{
		auto iter = Find(key);

		if (iter != end())
		{
			std::uint32_t hashIndex = mHashFunctor(key) % mBucketCount;
			mBuckets[hashIndex].Remove(*iter);
			mSize--;
		}
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	TValue& HashMap<TKey, TValue, HashFunctor>::operator[](const TKey& key)
	{
		PairType newPair(key, TValue());
		auto iter = Insert(newPair);
		return iter->second;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	const TValue& HashMap<TKey, TValue, HashFunctor>::operator[](const TKey& key) const
	{
		auto iter = Find(key);
		if (iter == end()) { throw std::exception("Indexing out of bounds on const HashMap"); }
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
	void HashMap<TKey, TValue, HashFunctor>::Clear()
	{
		for (std::uint32_t i = 0; i < mBucketCount; i++)
		{
			mBuckets[i].Clear();
		}

		mSize = 0;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	std::uint32_t HashMap<TKey, TValue, HashFunctor>::Size() const
	{
		return mSize;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	bool HashMap<TKey, TValue, HashFunctor>::ContainsKey(const TKey& key) const
	{
		auto iter = Find(key);
		return iter != end();
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator():
		mOwner(nullptr), mBucketIndex(0), mIter(Library::Vector<PairType>::Iterator()) 
	{}

	template <typename TKey, typename TValue, typename HashFunctor>
	HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator(const Iterator& rhs) :
		mOwner(rhs.mOwner), mBucketIndex(rhs.mBucketIndex), mIter(rhs.mIter) 
	{}

	template <typename TKey, typename TValue, typename HashFunctor>
	HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator(const HashMap<TKey, TValue, HashFunctor>* owner, const std::uint32_t& bucketIndex, typename Library::Vector<PairType>::Iterator iter) :
		mOwner(owner), mBucketIndex(bucketIndex), mIter(iter) 
	{}

	template <typename TKey, typename TValue, typename HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::Iterator& HashMap<TKey, TValue, HashFunctor>::Iterator::operator=(const Iterator& rhs)
	{
		if (rhs.mOwner == nullptr) { throw std::exception("Right hand side owner is null"); }
		mOwner = rhs.mOwner;
		mBucketIndex = rhs.mBucketIndex;
		mIter = rhs.mIter;
		return *this;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	typename HashMap<TKey, TValue, HashFunctor>::Iterator& HashMap<TKey, TValue, HashFunctor>::Iterator::operator++()
	{
		if (mOwner == nullptr) { throw std::exception("Incrementing beyond HashMap bounds"); }
		
		if (mBucketIndex < mOwner->mBucketCount)
		{	// As long as we are within proper range, don't bypass increment
			++mIter;
			while (mIter == mOwner->mBuckets[mBucketIndex].end())
			{
				if (++mBucketIndex < mOwner->mBucketCount)
				{
					mIter = mOwner->mBuckets[mBucketIndex].begin();
				}
				else break;
			}
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
		if (mOwner == nullptr) { throw std::exception("Attempting to dereference null iterator"); }
		return (*mIter);
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	const typename HashMap<TKey, TValue, HashFunctor>::PairType& HashMap<TKey, TValue, HashFunctor>::Iterator::operator*() const
	{
		if (mOwner == nullptr) { throw std::exception("Attempting to dereference null iterator"); }
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
		if (mOwner == nullptr) { throw std::exception("Owner is null"); }

		return mOwner == rhs.mOwner &&
			mBucketIndex == rhs.mBucketIndex &&
			mIter == rhs.mIter;
	}

	template <typename TKey, typename TValue, typename HashFunctor>
	bool HashMap<TKey, TValue, HashFunctor>::Iterator::operator!=(const Iterator& rhs) const
	{
		if (mOwner == nullptr) { throw std::exception("Owner is null"); }
		return !(operator==(rhs));
	}
}
