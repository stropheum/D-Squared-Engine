#pragma once
#include <cstdint>

namespace Vector
{
	/// @Class Vector: A templated dynamically allocated array
	/// @Author: Dale Diaz
	///
	/// An implementation of vector which lazily loads memory as needed. Default
	/// capacity is 10 elements, but can be resized manually and shrunk to fit 
	/// the current data set. Iterators are used to increment over the data without
	/// causing any memory corruption
	template <class T> class Vector
	{
	public:
		class Iterator; /// Forward declaration of Iterator class
		
		/// Default constructor
		Vector();

		/// Copy constructor
		/// @Param rhs: The Vector being copied
		Vector(const Vector<T>& rhs);

		/// Rhs copy constructor
		Vector(Vector<T>&& rhs);

		/// Comparison operator
		/// @Param rhs: Vector being compared against
		bool operator==(const Vector<T>& rhs);

		/// Assignment operator
		/// @Param rhs: Vector being copied
		/// @Return: A copy of the right hand side Vector
		Vector<T>& operator=(const Vector<T>& rhs);

		/// Rhs assignment operator
		/// @Param rhs: Vector being copied
		/// @Return: A copy of the right hand side Vector
		Vector<T>& operator=(Vector&& rhs);

		/// Destructor
		~Vector();

		/// Finds a value in the Vector, if it exists
		/// @Param value: Value being searched for
		/// @Return: An iterator pointing to the value if it exists, end() otherwise
		Iterator find(const T& value);

		/// @Return: An iterator pointing to the first element in the Vector
		Iterator begin();

		/// @return: An iterator pointing past the last element in the Vector
		Iterator end();

		/// @Return: A reference to the first element in the Vector
		T& front();

		/// @Return: A reference to the last element in the Vector
		T& back();

		/// Searches for an element in the Vector by index
		/// @Param index: The index being retrieved
		/// @Return: A reference to the element at the specified index. Throws exception if out of bounds
		T& at(const std::uint32_t index);

		/// Searches for an element in the Vector by index
		/// @Param index: The index being retrieved
		/// @Return: A reference to the element at the specified index. Throws exception if out of bounds
		T& operator[](const std::uint32_t index);

		/// Const version of the index operator
		/// @Param index: The index being retrieved
		/// Retrun: A const reference to the element at the specified index. Throws exception if out of bounds
		const T& operator[](const std::uint32_t index) const;

		/// removes the last element pushed to the back of the Vectr
		void popBack();

		/// @Return: The current number of elements in the Vector
		std::uint32_t size() const;

		/// @Return: The current number of allocated positions for data
		std::uint32_t capacity() const;

		/// @Return: True if there are zero elements in Vector
		bool isEmpty() const;

		/// Adds an element to the first empty index available
		/// If there is no available capacity, reserve is called with 10 additional elements
		void pushBack(const T& value);

		/// Reserves space in the Vector for more elements
		/// @Param capacity: The new capacity of the Vector
		/// If capacity is less then current capacity, capacity is shrunk to the new size
		/// If capacity is less than current size, capacity is clamped to size
		void reserve(std::uint32_t capacity);

		/// Removes all elements from the Vector, sets size and capacity to zero and frees all memory
		void clear();

		/// Removes the first instance of a value from the Vector
		/// @Param value: The value being removed from the Vector
		/// If value does not exist, nothing happens
		void remove(const T& value);

		/// Clamps the capacity to the Vector's current number of elements
		void shrinkToFit();

	private:
		T* mBuffer; /// The space where elements will be stored
		std::uint32_t mSize; /// The number of elements in the Vector
		std::uint32_t mCapacity; /// The number of elements memory has been allocated for
		static const std::uint32_t CAPACITY_INCREMENT = 10; /// Standard reserve value increment
	public:
		class Iterator
		{
			friend class Vector;
		public:
			/// Default constructor
			Iterator();

			/// Copy constructor
			/// @Param rhs: The Iterator being copied
			Iterator(const Iterator& rhs);

			/// Assignment operator
			/// @Param rhs: The Iterator being copied
			Iterator& operator=(const Iterator& rhs);

			/// Equality comparison operator
			/// @Param rhs: The Iterator which is being compared against
			bool operator==(const Iterator& rhs);

			/// Pre-increment operator
			Iterator& operator++();

			/// Post-increment operator
			Iterator operator++(int);

			/// Dereference operator
			T& operator*();
		private:
			/// Internal Iterator constructor
			/// @Param owner: The Vector that owns this Iterator object
			/// @Param index: The location that this iterator points to
			Iterator(Vector<T>* owner, const std::uint32_t index);
			Vector<T>* mOwner; /// The vector that owns this Iterator
			std::uint32_t mIndex; /// The location that this iterator points to
		};
	};
}

#include "Vector.inl"