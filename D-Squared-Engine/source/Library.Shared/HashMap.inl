#pragma once
#include <cstdint>
#include "Vector.h"


namespace Library
{
    template <typename TKey, typename TValue, typename HashFunctor>
    HashMap<TKey, TValue, HashFunctor>::HashMap(std::uint32_t bucketCount) :
        m_bucketCount(bucketCount), m_buckets(), m_size(0)
    {	// HashMaps need to be constructed with At least one bucket, or nothing will be able to be stored
        if (m_bucketCount == 0) { throw std::exception("HashMap constructed with an invalid amount of buckets"); }
        InitializeBuckets();
    }

    template <typename TKey, typename TValue, typename HashFunctor>
    HashMap<TKey, TValue, HashFunctor>::HashMap(const HashMap<TKey, TValue, HashFunctor>& rhs) :
        m_bucketCount(rhs.m_bucketCount), m_buckets(rhs.m_buckets), m_size(rhs.m_size)
    {}

    template <typename TKey, typename TValue, typename HashFunctor>
    HashMap<TKey, TValue, HashFunctor>&
        HashMap<TKey, TValue, HashFunctor>::operator=(const HashMap<TKey, TValue, HashFunctor>& rhs)
    {
        if (this != &rhs)
        {
            m_bucketCount = rhs.m_bucketCount;
            m_buckets = rhs.m_buckets;
            m_size = rhs.m_size;
            m_hashFunctor = rhs.m_hashFunctor;
        }
        return *this;
    }

    template <typename TKey, typename TValue, class HashFunctor>
    HashMap<TKey, TValue, HashFunctor>::HashMap(HashMap<TKey, TValue, HashFunctor>&& rhs) noexcept :
        m_bucketCount(0), m_hashFunctor(), m_buckets(), m_size(0)
    {
        operator=(std::move(rhs));
    }

    template <typename TKey, typename TValue, class HashFunctor>
    HashMap<TKey, TValue, HashFunctor>& HashMap<TKey, TValue, HashFunctor>::operator=(HashMap<TKey, TValue, HashFunctor>&& rhs)
    {
        m_buckets = std::move(rhs.m_buckets);
        m_size = rhs.m_size;
        m_bucketCount = rhs.m_bucketCount;
        m_hashFunctor = rhs.m_hashFunctor;

        rhs.m_buckets.Clear();
        rhs.m_size = 0;
        rhs.m_bucketCount = 0;

        return *this;
    }

    template <typename TKey, typename TValue, typename HashFunctor>
    void HashMap<TKey, TValue, HashFunctor>::InitializeBuckets()
    {
        m_size = 0;
        for (std::uint32_t i = 0; i < m_bucketCount; i++)
        {	// Create a vector to represent each "bucket:
            m_buckets.PushBack(BucketType());
        }
        m_buckets.ShrinkToFit();
    }

    template <typename TKey, typename TValue, typename HashFunctor>
    typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::Find(const TKey& key) const
    {
        if (m_buckets.IsEmpty()) throw std::exception("Buckets are null");
        std::uint32_t hashIndex = m_hashFunctor(key) % m_bucketCount;
        auto& bucket = m_buckets[hashIndex];

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
            m_size++;
            std::uint32_t bucketIndex = m_hashFunctor(entry.first) % m_bucketCount;
            auto vIter = m_buckets[bucketIndex].PushBack(entry);
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
            m_size++;
            std::uint32_t bucketIndex = m_hashFunctor(entry.first) % m_bucketCount;
            auto vIter = m_buckets[bucketIndex].PushBack(entry);
            iter = HashMap<TKey, TValue>::Iterator(this, bucketIndex, vIter);
        }
        else
        {
            found = true;
        }

        return iter;
    }

    template <typename TKey, typename TValue, typename HashFunctor>
    void HashMap<TKey, TValue, HashFunctor>::Remove(const TKey& key)
    {
        auto iter = Find(key);

        if (iter != end())
        {
            std::uint32_t hashIndex = m_hashFunctor(key) % m_bucketCount;
            m_buckets[hashIndex].Remove(*iter);
            m_size--;
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

        if (m_size > 0)
        {
            std::uint32_t index = 0;
            auto iter = m_buckets[index].begin();
            while (iter == m_buckets[index].end() && index + 1 < m_bucketCount)
            {
                iter = m_buckets[++index].begin();
            }
            result = Iterator(this, index, iter);
        }

        return result;
    }

    template <typename TKey, typename TValue, typename HashFunctor>
    typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::end() const
    {
        return Iterator(this, m_bucketCount, m_buckets[m_bucketCount - 1].end());
    }

    template <typename TKey, typename TValue, typename HashFunctor>
    void HashMap<TKey, TValue, HashFunctor>::Clear()
    {
        for (std::uint32_t i = 0; i < m_bucketCount; i++)
        {
            m_buckets[i].Clear();
        }

        m_size = 0;
    }

    template <typename TKey, typename TValue, typename HashFunctor>
    std::uint32_t HashMap<TKey, TValue, HashFunctor>::Size() const
    {
        return m_size;
    }

    template <typename TKey, typename TValue, typename HashFunctor>
    bool HashMap<TKey, TValue, HashFunctor>::ContainsKey(const TKey& key) const
    {
        auto iter = Find(key);
        return iter != end();
    }

    template <typename TKey, typename TValue, typename HashFunctor>
    HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator() :
        m_owner(nullptr), m_bucketIndex(0), m_iter(Library::Vector<PairType>::Iterator())
    {}

    template <typename TKey, typename TValue, typename HashFunctor>
    HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator(const Iterator& rhs) :
        m_owner(rhs.m_owner), m_bucketIndex(rhs.m_bucketIndex), m_iter(rhs.m_iter)
    {}

    template <typename TKey, typename TValue, typename HashFunctor>
    HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator(const HashMap<TKey, TValue, HashFunctor>* owner, const std::uint32_t& bucketIndex, typename Library::Vector<PairType>::Iterator iter) :
        m_owner(owner), m_bucketIndex(bucketIndex), m_iter(iter)
    {}

    template <typename TKey, typename TValue, typename HashFunctor>
    typename HashMap<TKey, TValue, HashFunctor>::Iterator& HashMap<TKey, TValue, HashFunctor>::Iterator::operator=(const Iterator& rhs)
    {
        if (rhs.m_owner == nullptr) { throw std::exception("Right hand side owner is null"); }
        m_owner = rhs.m_owner;
        m_bucketIndex = rhs.m_bucketIndex;
        m_iter = rhs.m_iter;
        return *this;
    }

    template <typename TKey, typename TValue, typename HashFunctor>
    typename HashMap<TKey, TValue, HashFunctor>::Iterator& HashMap<TKey, TValue, HashFunctor>::Iterator::operator++()
    {
        if (m_owner == nullptr) { throw std::exception("Incrementing beyond HashMap bounds"); }

        if (m_bucketIndex < m_owner->m_bucketCount)
        {	// As long as we are within proper range, don't bypass increment
            ++m_iter;
            while (m_iter == m_owner->m_buckets[m_bucketIndex].end())
            {
                if (++m_bucketIndex < m_owner->m_bucketCount)
                {
                    m_iter = m_owner->m_buckets[m_bucketIndex].begin();
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
        if (m_owner == nullptr) { throw std::exception("Attempting to dereference null iterator"); }
        return (*m_iter);
    }

    template <typename TKey, typename TValue, typename HashFunctor>
    const typename HashMap<TKey, TValue, HashFunctor>::PairType& HashMap<TKey, TValue, HashFunctor>::Iterator::operator*() const
    {
        if (m_owner == nullptr) { throw std::exception("Attempting to dereference null iterator"); }
        return (*m_iter);
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
        if (m_owner == nullptr) { throw std::exception("Owner is null"); }

        return m_owner == rhs.m_owner &&
            m_bucketIndex == rhs.m_bucketIndex &&
            m_iter == rhs.m_iter;
    }

    template <typename TKey, typename TValue, typename HashFunctor>
    bool HashMap<TKey, TValue, HashFunctor>::Iterator::operator!=(const Iterator& rhs) const
    {
        if (m_owner == nullptr) { throw std::exception("Owner is null"); }
        return !(operator==(rhs));
    }
}