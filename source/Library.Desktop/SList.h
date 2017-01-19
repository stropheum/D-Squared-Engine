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

	/**
	* Push an object to the front of the list
	* @Param data: The data being pushed to the front of the list
	*/
	void pushFront(T data);

	/**
	* Push an object to the back of the list
	* @Param data: The data being pushed to the back of the list
	*/
	void pushBack(T data);

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

	/**
	* Retrieves the back item on the list
	* @Return The templated item at the back of the list
	*/
	T& back();

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

		/// Data being contained by the node
		T mData;

		/// Pointer to the node that this node is linked to
		Node* next;
	};

	/// Number of elements in the list
	int mSize;

	/// Front node in the list
	Node* mFront;

	/// Back node in the list
	Node* mBack;
};

#include "SList.inl"
