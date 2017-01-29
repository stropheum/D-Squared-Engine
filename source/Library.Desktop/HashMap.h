#pragma once
#include <cstdint>
#include <utility>
#include <functional>

namespace HashMap
{
	template <class TKey, class TData> class HashMap
	{
		typedef std::pair<TKey, TData> PairType;

	public:
		class Iterator; /// Forward declaration of Iterator class

		/// Constructor for HashMap
		/// @Param hashTableSize: The predefined 
		HashMap(std::uint32_t hashTableSize, std::function<int(TData)> HashFunctor=nullptr);
		
		/// Destructor
		~HashMap();
		
		/// Copy constructor
		/// @Param rhs: Constant reference to the HashMap being copied
		HashMap(const HashMap<TKey, TData>& rhs);

		/// Move semantics (disabled);
		HashMap(HashMap<TKey, TData>&& rhs) = delete;

		/// Assignment operator
		/// @Param rhs: Constant reference to the HAshMap being copied
		/// @Return: A deep copy of the right-hand HashMap 
		HashMap<TKey, TData>& operator=(const HashMap<TKey, TData>& rhs);


		/// Finds an instance of a key in the HashMap and returns its associated value
		/// @Param rhs: constant reference to the key being searched for
		/// @Return: An Iterator containing the found PairType, end otherwise
		Iterator find(const TKey& key) const;

		/// Inserts a Pairtype into the HashMap
		/// @Param entry: The PairType being added to the HashMap
		/// @Return: An Iterator pointing to the inserted PairType
		Iterator insert(const PairType& entry);

		/// Index-of operator
		/// @Param key: Key being used as an index for the HashMap element
		/// @Return: A reference to the data associated with the key
		TData& operator[](const TKey& key);
	private:
		std::function<void()> mHashFunctor;
	public:
		class Iterator
		{
			friend class HashMap;
		public:
			Iterator();
		private:
			Iterator(const HashMap<TKey, TData>* owner, const TKey& key, const TData& data);
			const HashMap<TKey, TData>* mOwner;
			PairType mPair;
		};
	};
}

#include "HashMap.inl"