#pragma once
#include <cstdint>

namespace HashMap
{
#define HashMapTemplate template <typename TKey, typename TData, typename HashFunctor>
#define Params TKey, TData, HashFunctor

	template <class TKey, class TData, class HashFunctor>
	::HashMap::HashMap<TKey, TData, HashFunctor>::HashMap(std::uint32_t hashTableSize)
	{
		UNREFERENCED_PARAMETER(hashTableSize);
		//TODO: implement constructor
	}

	template <class TKey, class TData, class HashFunctor>
	HashMap<TKey, TData, HashFunctor>::~HashMap()
	{
		//TODO: Implement destructor
	}

	template <class TKey, class TData, class HashFunctor>
	HashMap<TKey, TData, HashFunctor>::HashMap(const HashMap<TKey, TData, HashFunctor>& rhs)
	{
		//TODO: Implement copy constructor
	}

	template <class TKey, class TData, class HashFunctor>
	HashMap<TKey, TData, HashFunctor>& HashMap<TKey, TData, HashFunctor>::operator=(const HashMap<TKey, TData, HashFunctor>& rhs)
	{
		//TODO: Implement assignment operator
		return *this;
	}

	template <class TKey, class TData, class HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::find(const TKey& key)
	{
		//TODO: Implement find method
	}

	template <class TKey, class TData, class HashFunctor>
	TData& HashMap<TKey, TData, HashFunctor>::operator[](const TKey& key)
	{
	}
}
