#pragma once
#include <cstdint>


namespace Library
{
	template <class T> class SList
	{
		class Node;

	public:

		class Iterator;

#pragma region Construction/Copy/Assignment

		SList();

		~SList();
		
		SList(const SList<T>& rhs);

		SList<T>& operator=(const SList<T>& rhs);

		SList(SList&& rhs) = delete;

		SList& operator=(SList&& rhs) = delete;

#pragma endregion

		/**
		 * Push an object to the Front of the list
		 * @Param data: The data being pushed to the Front of the list
		 * @Return: Iterator pointing to the Front of the list
		 */
		Iterator PushFront(const T& data);

		/**
		 * Push an object to the Back of the list
		 * @Param data: The data being pushed to the Back of the list
		 * @Return: Iterator pointing to the Back of the list
		 */
		Iterator PushBack(const T& data);

		/**
		 * Removes all items in the list
		 */
		void Clear();

		/**
		 * Pops the front value off of the list
		 * @Return: The value At the Front of the list
		 */
		T PopFront();

		/**
		 * Peeks the front value from the front of the list
		 * @Return: The template item At the Front of the list
		 */
		T& Front();

		/**
		 * Peeks the front value from the front of the list
		 * @Return: A const reference to the template item At the Front of the list
		 */
		const T& Front() const;

		/**
		 * Peeks the back value of the list
		 * @Return: The templated item At the Back of the list
		 */
		T& Back();

		/**
		 * Peeks the back value of the list
		 * @Return: A const reference to the templated item At the Back of the list
		 */
		const T& Back() const;

		/**
		 * Determines if the list has no elements in it
		 * @Return: True if the list does not contain any elements
		 */
		bool IsEmpty() const;

		/**
		 * Determines the number of elements in the list
		 * @Return: The Size of the list
		 */
		std::uint32_t Size() const;

		/**
		 * Accessor for the iterator pointing to the beginning of the list
		 * @Return: An iterator that points to the Front node
		 */
		Iterator begin() const;

		/**
		* Accessor for the iterator pointing to the end of the list
		* @Return: An iterator that points to the back node
		*/
		Iterator end() const;

		/**
		 * Inserts a value after the value in a given iterator
		 * @Param value: The value being inserted into the list
		 * @Param location: The point where the value is being inserted after
		 * @Return: An Iterator to the location of the inserted value
		 */
		Iterator InsertAfter(const T& value, const Iterator& location);

		/**
		 * Finds an item in the list
		 * @Param value: The value being found from the list
		 * @Return: An iterator pointing to the value if it exists in the list, end otherwise
		 */
		Iterator Find(const T& value) const;

		/**
		 * Removes the first instance of a value from the list
		 * @Param value: The value being removed from the list
		 */
		void Remove(const T& value);

		class Iterator
		{
			friend class SList;

		public:
			
			/**
			 * Constructor. Takes a node reference and assigns owner to current SList object
			 */
			Iterator();

			/**
			 * Copy constructor. Creates new Iterator with identical member references
			 * @Param rhs: The iterator reference being copied
			 */
			Iterator(const Iterator& rhs);

			/**
			 * Assignment operator. Assigns member references to the rhs member references
			 * @Param rhs: The iterator reference that this object is being assigned to
			 */
			Iterator& operator=(const Iterator& rhs);

			/**
			 * Comparison operator
			 * @Param rhs: The iterator reference being compared to
			 * @Return: True if owners and node references are identical
			 */
			bool operator==(const Iterator& rhs) const;

			/**
			 * Not equals operator
			 * @Param rhs: The iterator reference being compared to
			 * @Return: negation of operator==
			 */
			bool operator!=(const Iterator& rhs) const;

			/**
			 * Prefix increment operator. Sets node reference to its linked node
			 */
			Iterator& operator++();

			/**
			 * Postfix increment operator. Calls prefix increment operator
			 */
			Iterator operator++(int);

			/**
			 * Dereference operator
			 * @Return: A reference to the T member that the iterator's node points to
			 */
			T& operator*();

		private:
			
			/**
			 * Constructor
			 * @Param owner: The owner container of the iterator object
			 * @Param node: The member node that the iterator refers to
			 */
			Iterator(SList<T>* owner, Node* node);

			const SList<T>* mOwner; // The container that owns this iterator
			Node* mNode;			// The node that this iterator points to

		};

	private:

		class Node
		{
		public:
			
#pragma region Node Construction/Copy/Assignment

			explicit Node(T data) : mData(data), mNext(nullptr) {}

			~Node() {}

			Node(const Node& rhs) = default;

			Node& operator=(const Node& rhs) = delete;

			Node(Node&& rhs) = delete;

			Node& operator=(Node&& rhs) = delete;

#pragma endregion

			T& Data() { return mData; }

			Node*& Next() { return mNext; }

		private:

			T mData; // Data being contained by the node
			Node* mNext; // Pointer to the node that this node is linked to

		};

		std::uint32_t mSize; // Number of elements in the list
		Node* mFront; // Front node in the list
		Node* mBack; // Back node in the list
	};


}
#include "SList.inl"