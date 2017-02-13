#pragma once
#include <cstdint>

/// @Class SList: Singularly-Linked List
/// @Author: Dale Diaz
///
/// An implementation of linked list which allows for dynamic adding of template items 
/// Items can be added indefinitely, ensured to be of the template type, and are only 
/// exposed via method calls to front and back, which return references to the data at 
/// those respective nodes, and dereferencing and iterator object    
namespace Library
{
	template <class T> class SList
	{
		class Node;		/// Node class forward declaration
	public:
		class Iterator; /// Iterator class forward declaration

		SList();		/// Default constructor
		
		/// Copy constructor using deep copy semantics
		/// @Param rhs: SList being copied
		SList(const SList<T>& rhs);

		/// Assignment operator
		/// @Param rhs: Const reference to the SList being copied
		/// @Return: Reference to a copy of the SList
		SList<T>& operator=(const SList<T>& rhs);

		/// Destructor which De-allocates every object in the list individually
		~SList();

		/// Push an object to the front of the list
		/// @Param data: The data being pushed to the front of the list
		/// @Return: Iterator pointing to the front of the list
		Iterator pushFront(const T& data);

		/// Push an object to the back of the list
		/// @Param data: The data being pushed to the back of the list
		/// @Return: Iterator pointing to the back of the list
		Iterator pushBack(const T& data);

		/// Removes all items in the list
		void clear();

		/// @Return: The value at the front of the list
		T popFront();

		/// @Return: The template item at the front of the list
		T& front();

		/// @Return: A const reference to the template item at the front of the list
		const T& front() const;

		/// @Return: The templated item at the back of the list
		T& back();

		/// @Return: A const reference to the templated item at the back of the list
		const T& back() const;

		/// @Return: True if the list does not contain any elements
		bool isEmpty() const;

		/// @Return: The size of the list
		std::uint32_t size() const;

		/// @Return: An iterator that points to the front node
		Iterator begin();

		/// @Return:  an iterator that points to the mNext node of the back node
		Iterator end();

		/// Inserts a value after the value in a given iterator
		/// @Param value: The value being inserted into the list
		/// @Param location: The point where the value is being inserted after
		/// @Return: An Iterator to the location of the inserted value
		Iterator insertAfter(const T& value, const Iterator& location);

		/// Finds an item in the list
		/// @Param value: The value being found from the list
		/// @Return: An iterator pointing to the value if it exists in the list, end otherwise
		Iterator find(const T& value);

		/// Removes the first instance of a value from the list
		/// @Param value: The value being removed from the list
		void remove(T value);

		class Iterator
		{
			friend class SList;
		public:
			/// Constructor. Takes a node reference and assigns owner to current SList object
			Iterator() = default;

			/// Copy constructor. Creates new Iterator with identical member references
			/// @Param rhs: The iterator reference being copied
			Iterator(const Iterator& rhs);

			/// Assignment operator. Assigns member references to the rhs member references
			/// @Param rhs: The iterator reference that this object is being assigned to
			Iterator& operator=(const Iterator& rhs);

			/// Comparison operator
			/// @Param rhs: The iterator reference being compared to
			/// @Return: True if owners and node references are identical
			bool operator==(const Iterator& rhs) const;

			/// Not equals operator
			/// @Param rhs: The iterator reference being compared to
			/// @Return: negation of operator==
			bool operator!=(const Iterator& rhs) const;

			/// Prefix increment operator. Sets node reference to its linked node
			Iterator operator++();

			/// Postfix increment operator. Calls prefix increment operator
			Iterator operator++(int);

			/// Dereference operator
			/// @Return: A reference to the T member that the iterator's node points to
			T& operator*();
		private:
			/// Constructor
			/// @Param owner: The owner container of the iterator object
			/// @Param node: The member node that the iterator refers to
			Iterator(SList<T>* owner, Node* node);

			const SList<T>* mOwner; /// The container that owns this iterator
			Node* mNode;			/// The node that this iterator points to
		};

	private:
		class Node
		{
		public:
			/// Constructor
			/// @Param data: The value contained in the node
			Node(T data) : mData(data), mNext(nullptr) {}

			/// Node destructor
			~Node() {}

			/// Default copy constructor
			Node(const Node& rhs) = default;

			T mData;     /// Data being contained by the node
			Node* mNext;  /// Pointer to the node that this node is linked to
		};

		std::uint32_t mSize; /// Number of elements in the list

		Node* mFront;    /// Front node in the list
		Node* mBack;     /// Back node in the list
	};


}
#include "SList.inl"