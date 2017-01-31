#pragma once
#include <cstdint>
#include <utility>
#include <functional>
#include "Vector.h"

namespace HashMap
{
	template <class TKey, class TValue> class HashMap
	{
		typedef std::pair<TKey, TValue> PairType;
		typedef Vector::Vector<PairType> BucketType;

	public:
		class Iterator; /// Forward declaration of Iterator class

		/// Default constructor for HashMap
		/// HashMap size will default to 13
		/// Default hash functor will be used
		HashMap();

		/// Constructor for HashMap
		/// @Param hashMapSize: The predefined 
		HashMap(std::uint32_t hashMapSize, std::function<std::uint32_t(TKey)> hashFunctor=defaultHashFunctor);

		/// Destructor
		~HashMap();
		
		/// Copy constructor
		/// @Param rhs: Constant reference to the HashMap being copied
		HashMap(const HashMap<TKey, TValue>& rhs);

		/// Move semantics (disabled);
		HashMap(HashMap<TKey, TValue>&& rhs) = delete;

		/// Assignment operator
		/// @Param rhs: Constant reference to the HAshMap being copied
		/// @Return: A deep copy of the right-hand HashMap 
		HashMap<TKey, TValue>& operator=(const HashMap<TKey, TValue>& rhs);


		/// Finds an instance of a key in the HashMap and returns its associated value
		/// @Param rhs: constant reference to the key being searched for
		/// @Return: An Iterator containing the found PairType, end otherwise
		void find(const TKey& key) const;
		//TODO: Change return type back to iterator once implemented

		/// Inserts a Pairtype into the HashMap
		/// @Param entry: The PairType being added to the HashMap
		/// @Return: An Iterator pointing to the inserted PairType
		Iterator insert(const PairType& entry);

		/// Index-of operator
		/// @Param key: Key being used as an index for the HashMap element
		/// @Return: A reference to the data associated with the key
		TValue& operator[](const TKey& key);

		/// Clears all memory stored in the HashMap
		void clear();
	private:
		std::uint32_t mHashMapSize;
		std::function<std::uint32_t(TKey key)> mHashFunctor;
		Vector::Vector<BucketType> mBuckets;

		static const uint32_t defaultHashMapSize = 13; // If no size is specified, number of buckets defaults to 13

		/// Simple hash algorithm to determine which bucket the data will be placed into
		/// @Param key: Key being used to determine index of HashMap element
		/// @Param hashMapSize: The number of buckets in the HashMap
		static std::uint32_t defaultHashFunctor(const TKey& key);

		Iterator begin();

		/// Creates one vector of type TData for each bucket in the specified size
		void initializeBuckets();

	public:
		class Iterator
		{
			friend class HashMap;
		public:
			Iterator();
			Iterator& operator++();
			Iterator operator++(int);
			Iterator begin();
			Iterator end();
		private:
//			Vector::Vector<PairType>::Iterator(const HashMap<TKey, TValue>* owner, Vector::Vector<PairType>::Iterator iter);
			Iterator(const HashMap<TKey, TValue>* owner, typename Vector::Vector<PairType>::Iterator iter);

			const HashMap<TKey, TValue>* mOwner;
			std::uint32_t mBucketIndex;
			typename Vector::Vector<BucketType>::Iterator mIter;
		};
	};
}

#include "HashMap.inl"