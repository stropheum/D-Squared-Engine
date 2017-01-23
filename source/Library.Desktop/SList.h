#pragma once
#include "pch.h"
#include "windows.h"


template <class T> class SList
{
public:

	/// Default constructor
	SList();

	/// Copy constructor using deep copy semantics
	explicit SList(const SList<T>& obj);

	/**
	 * Assignment operator
	 * @Param rhs: Const refrence to the SList being copied
	 * @Return: Reference to a copy of the SList
	 */
	SList<T>& operator=(const SList<T>& rhs);

	/// Deconstructor which De-allocates every object in the list individually
	~SList();

	class Iterator;
	/**
	* Push an object to the front of the list
	* @Param data: The data being pushed to the front of the list
	*/
	Iterator pushFront(T data);

	/**
	* Push an object to the back of the list
	* @Param data: The data being pushed to the back of the list
	*/
	Iterator pushBack(T data);

	/// Removes all items in the list
	void clear();

	/**
	* Pop and object to the front of the list
	* @Return: The value at the front of the list
	*/
	T popFront();

	/**
	* Retrieves the front item on the list
	* @Return The templated item at the front of the list
	*/
	T& front();

	const T& front() const;

	/**
	* Retrieves the back item on the list
	* @Return The templated item at the back of the list
	*/
	T& back();

	const T& back() const;

	/**
	* Determines if the list does not contain any elements
	* @Return true if the list is empty
	*/
	bool isEmpty() const;

	/**
	* Retrieves the size of the list
	* @Return The list's size
	*/
	int size() const;

private:
	class Node; /// Forward declaration of node class
public:
	class Iterator
	{
		friend class SList;
	public:
		/// Constructor. Takes a node reference and assigns owner to current SList object
		Iterator() = default;
		Iterator(const Iterator& rhs);
		Iterator& operator=(const Iterator& rhs);
		bool operator==(Iterator& rhs);
		bool operator!=(Iterator& rhs);
		void operator++();
		void operator++(int);
		T& operator*();
	private:
		Iterator(SList<T>* owner, Node* node);
		const SList<T>* mOwner;
		Node* mNode;
	};

	Iterator& begin();
	Iterator& end();

private:
	class Node
	{
	public:
		/// Default node constructor
		Node() : mData(nullptr), next(nullptr) {}

		/**
		 * Constructor
		 * @Param data: The value contained in the node
		 */
		explicit Node(T data) : mData(data), next(nullptr) {}

		/// Node deconstructor
		~Node(){}
		Node(const Node& rhs) = delete;

		T mData;    /// Data being contained by the node
		Node* next; /// Pointer to the node that this node is linked to
	};
	
	int mSize;    /// Number of elements in the list
	Node* mFront; /// Front node in the list
	Node* mBack;  /// Back node in the list

	Iterator mBegin; /// Beginning of iterator
	Iterator mEnd;   /// End of iterator
};

#include "SList.inl"
#include "Iterator.inl"