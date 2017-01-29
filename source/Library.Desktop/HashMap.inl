#pragma once
#include <cstdint>
#include <functional>

namespace HashMap
{
#define HashMapTemplate typename TKey, typename TData

	template <HashMapTemplate>
	HashMap<TKey, TData>::HashMap(std::uint32_t hashTableSize, std::function<int(TData)> HashFunctor=nullptr) 
	{
		UNREFERENCED_PARAMETER(hashTableSize);
		//TODO: implement constructor
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

	template <HashMapTemplate>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::find(const TKey& key) const
	{
		//TODO: Implement find method
	}

	template <HashMapTemplate>
	TData& HashMap<TKey, TData>::operator[](const TKey& key)
	{
		//TODO: Implement index of operator
	}

	template <HashMapTemplate>
	HashMap<TKey, TData>::Iterator::Iterator(const HashMap<TKey, TData>* owner, const TKey& key, const TData& data) :
		mOwner(owner), mPair(key, data) {}
}
