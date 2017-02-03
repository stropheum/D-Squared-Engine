#pragma once
#include <cstdint>
#include <utility>
#include <functional>
#include "Vector.h"
#include "DefaultHash.h"

namespace HashMap
{
	template <typename TKey, typename TValue, class HashFunctor=DefaultHash<TKey>> class HashMap
	{
		/// The key/value pairs being used by the HashMap
		typedef std::pair<TKey, TValue> PairType;
		/// The buckets being used in the Vector chain. This implementation uses Vectors of PairTypes
		typedef Vector::Vector<PairType> BucketType;

	public:
		class Iterator; /// Forward declaration of Iterator class

		/// Constructor for HashMap
		/// @Param hashMapSize: The predefined 
		explicit HashMap(std::uint32_t hashMapSize);

		/// Virtual destructor to prevent inheritance
		virtual ~HashMap() = default;

		/// Copy constructor
		/// @Param rhs: Constant reference to the HashMap being copied
		HashMap(const HashMap<TKey, TValue, HashFunctor>& rhs);

		/// Move copy constructor (disabled);
		HashMap(HashMap<TKey, TValue, HashFunctor>&& rhs) = delete;

		/// Assignment operator
		/// @Param rhs: Constant reference to the HAshMap being copied
		/// @Return: A deep copy of the right-hand HashMap 
		HashMap<TKey, TValue, HashFunctor>& operator=(const HashMap<TKey, TValue, HashFunctor>& rhs);

		/// Move assignment operator (disabled)
		HashMap<TKey, TValue, HashFunctor>& operator=(const HashMap<TKey, TValue, HashFunctor>&& rhs) = delete;


		/// Finds an instance of a key in the HashMap and returns its associated value
		/// @Param rhs: constant reference to the key being searched for
		/// @Return: An Iterator containing the found PairType, end otherwise
		/// @Exception: Thrown if bucket chain is null
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
		/// @Return: True if the key exists in the HashMap
		bool containsKey(const TKey& key);

	private:
		std::uint32_t mHashMapSize;			 /// Number of buckets in the hash map.
		HashFunctor mHashFunctor;			 /// The hash function being used by this HashMap
		Vector::Vector<BucketType> mBuckets; /// Collection of buckets in the hash map

		static const uint32_t defaultHashMapSize = 13; // If no size is specified, number of buckets defaults to 13

		/// Creates one vector of type TData for each bucket in the specified size
		void initializeBuckets();

	public:
		class Iterator
		{
			friend class HashMap;
		public:
			/// Iterator constructor. Creates an Iterator pointing to nothing. Used for lazy initialization
			Iterator();

			/// Virtual destructor
			virtual ~Iterator() = default;

			/// Copy Constructor. Creates an iterator equivalent to the current Iterator
			/// @Param rhs: The Iterator being copied
			Iterator(const Iterator& rhs);

			/// Assignment Operator
			/// @Param rhs: The Iterator being assigned to
			/// @Return: A reference to the Iterator copy
			/// @Exception: Thrown if right hand side owner is null
			Iterator& operator=(const Iterator& rhs);

			/// Increment operator(prefix)
			/// @Return: A reference to the next Iterator in the HashMap
			/// @Exception: Thrown if incrementing beyond end of HashMap 
			Iterator& operator++();

			/// Increment operator(postfix)
			/// @Return: A copy of the Iterator before it has been incremented
			Iterator operator++(int);

			/// Dereference operator
			/// @Return: A reference to a PairType that the Iterator's member iterator is pointing to
			/// @Exception: Thrown if attempting to dereferencing the end of the HashMap
			PairType& operator*() const;
			
			/// Arrow operator
			/// @Return: A pointer to a PairType that the Iterator's member iterator is pointing to
			PairType* operator->() const;

			/// Equality operator
			/// @Param rhs: The Iterator being compared against
			/// @return: True if the two Iterators are equivalent
			/// @Exception: Thrown if owner is null
			bool operator==(const Iterator& rhs) const;

			/// Not-Equal operator
			/// @Param rhs: The Iterator being compared against
			/// @Return: False if the two Iterators are equivalent
			/// @Exception: Thrown if owner is null
			bool operator!=(const Iterator& rhs) const;
		private:
			/// Private constructor. Used for traversing the chained vectors
			/// @Param owner: The HashMap that owns this iterator
			/// @Param bucketIndex: The index into the Vector chain
			/// @Param iter: The iterator that mIter is being assigned to
			Iterator(const HashMap<TKey, TValue, HashFunctor>* owner, std::uint32_t bucketIndex, typename Vector::Vector<PairType>::Iterator iter);

			const HashMap<TKey, TValue, HashFunctor>* mOwner;	/// The HashMap that owns this Iterator
			std::uint32_t mBucketIndex;							/// The index into the Vector chain
			typename Vector::Vector<PairType>::Iterator mIter;	/// The Iterator on the Vector of PairTypes that is currently being iterated on
		};
	};
}

#include "HashMap.inl"