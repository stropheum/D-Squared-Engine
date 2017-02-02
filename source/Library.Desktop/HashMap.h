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
		HashMap(std::function<std::uint32_t(const TKey&)> hashFunctor=defaultHashFunctor);

		/// Constructor for HashMap
		/// @Param hashMapSize: The predefined 
		HashMap(std::uint32_t hashMapSize, std::function<std::uint32_t(const TKey&)> hashFunctor=defaultHashFunctor);

		/// Virtual destructor to prevent inheritance
		virtual ~HashMap() = default;

		/// Copy constructor
		/// @Param rhs: Constant reference to the HashMap being copied
		HashMap(const HashMap<TKey, TValue>& rhs);

		/// Move copy constructor (disabled);
		HashMap(HashMap<TKey, TValue>&& rhs) = delete;

		/// Assignment operator
		/// @Param rhs: Constant reference to the HAshMap being copied
		/// @Return: A deep copy of the right-hand HashMap 
		HashMap<TKey, TValue>& operator=(const HashMap<TKey, TValue>& rhs);

		/// Move assignment operator (disabled)
		HashMap<TKey, TValue>& operator-(const HashMap<TKey, TValue>&& rhs) = delete;


		/// Finds an instance of a key in the HashMap and returns its associated value
		/// @Param rhs: constant reference to the key being searched for
		/// @Return: An Iterator containing the found PairType, end otherwise
		Iterator find(const TKey& key) const;

		/// Inserts a Pairtype into the HashMap
		/// @Param entry: The PairType being added to the HashMap
		/// @Return: An Iterator pointing to the inserted PairType
		Iterator insert(const PairType& entry);

		/// Removes a PairType from the HashMap, if it exists. Otherwise does nothing
		/// @Param key: The key being used to search for the item in the HashMap
		void remove(const TKey& key);

		/// Index-of operator
		/// @Param key: Key being used as an index for the HashMap element
		/// @Return: A reference to the data associated with the key
		TValue& operator[](const TKey& key);

		/// Points to the first data point in the HashMap
		/// @Return: An iterator pointing to the first piece of data in the HashMap
		Iterator begin() const;

		/// Points to the end node in the last bucket in the HashMap
		/// @Return: An iterator pointing to the end of the last bucket in the HashMap
		Iterator end() const;

		/// Clears all memory stored in the HashMap
		void clear();

		/// The number of elements inserted into the HashMap
		/// @Return: The number of elements that have been inserted into the HashMap
		std::uint32_t size() const;

		/// Determines if a value has been inserted into the HashMap with the specified key
		/// @Param key: The key being searched for
		/// @Return: True if the key exists in the hashmap
		bool containsKey(const TKey& key);

	private:
		std::uint32_t mHashMapSize;								/// Number of buckets in the hash map.
		std::function<std::uint32_t(TKey key)> mHashFunctor;	/// Hash function used by the hash map
		Vector::Vector<BucketType> mBuckets;					/// Collection of buckets in the hash map

		static const uint32_t defaultHashMapSize = 13; // If no size is specified, number of buckets defaults to 13

		/// Simple hash algorithm to determine which bucket the data will be placed into
		/// @Param key: Key being used to determine index of HashMap element
		/// @Param hashMapSize: The number of buckets in the HashMap
		static std::uint32_t defaultHashFunctor(const TKey& key);

		/// Creates one vector of type TData for each bucket in the specified size
		void initializeBuckets();

	public:
		class Iterator
		{
			friend class HashMap;
		public:
			Iterator();
			virtual ~Iterator() = default;
			Iterator(const Iterator& rhs);
			Iterator& operator=(const Iterator& rhs);
			Iterator& operator++();
			Iterator operator++(int);
			PairType& operator*() const;
			PairType& operator->() const;
			bool operator==(const Iterator& rhs) const;
			bool operator!=(const Iterator& rhs) const;
		private:
			Iterator(const HashMap<TKey, TValue>* owner, std::uint32_t bucketIndex, typename Vector::Vector<PairType>::Iterator iter);

			const HashMap<TKey, TValue>* mOwner;
			std::uint32_t mBucketIndex;
			typename Vector::Vector<PairType>::Iterator mIter;
		};
	};
}

#include "HashMap.inl"