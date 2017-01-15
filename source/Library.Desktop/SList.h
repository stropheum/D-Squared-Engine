#pragma once
#include "pch.h"
#include "windows.h"

/**
 * Singularly Linked List
 */
template <class T> class SList
{
public:
	SList();
	explicit SList(SList<T>& obj);
	~SList();
	void pushFront(T data);
	void pushBack(T data);
	T popFront();
	T front();
	T back();
	bool isEmpty() const;
	int size() const;
	void clear();
	T& operator=(T rhs);
private:
	class Node
	{
	public:
		Node() : mData(nullptr), next(nullptr) {}
		explicit Node(T data) : mData(data), next(nullptr) {}
		~Node(){ mData = NULL; }
		T mData;
		Node* next;
	};
	int mSize;
	Node* mFront;
	Node* mBack;
};

/**
* Default constructor
*/
template <class T>
SList<T>::SList(): mSize(0), mFront(nullptr), mBack(nullptr)
{
}

/**
 * Copy Constructor
 * Performs a deep copy of every current element in the list
 */
template <class T>
SList<T>::SList(SList<T>& obj)
{
//	mFront = new Node(obj.front());
	auto size = obj.size();
	for (auto i = 0; i < size; i++)
	{
		auto value = obj.popFront();
		this->pushBack(value);
//		obj.pushFront(value);
	}
}

/**
* Deconstructor
*/
template <class T>
SList<T>::~SList()
{
	Node* current = mFront;
	while (current != nullptr)
	{
		Node* newCurrent = current->next;
		delete(current);
		current = newCurrent;
	}
}

/**
 * Push an object to the front of the list
 */
template <class T>
void SList<T>::pushFront(T data)
{
	auto temp = mFront;
	mFront = new Node(data);
	mFront->next = temp;
	mSize++;
}

/**
* Push an object to the back of the list
*/
template <class T>
void SList<T>::pushBack(T data)
{
	if (mFront == nullptr)
	{
		mFront = new Node(data);
	}
	else
	{
		auto current = mFront;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = new Node(data);
	}
	mSize++;
}

/**
 * Pop and object to the front of the list
 */
template <class T>
T SList<T>::popFront()
{
	auto oldFront = mFront;
	auto result = mFront->mData;
	mFront = mFront->next;
	delete(oldFront);
	mSize--;
	return result;
}

/**
* Retrieves the front item on the list
* @Return The templated item at the front of the list
*/
template <class T>
T SList<T>::front()
{
	return mFront->mData;
	//TODO: throw exception if trying to call front on a null list
}

/**
* Retrieves the back item on the list
* @Return The templated item at the back of the list
*/
template <class T>
T SList<T>::back()
{
	auto current = mFront;
	while (current->next != nullptr)
	{
		current = current->next;
	}
	return (current != nullptr) ? current->mData : NULL;
	//TODO: Throw exception if trying to call back on a null list
}

/**
 * Determines if the list does not contain any elements
 * @Return true if the list is empty
 */
template <class T>
bool SList<T>::isEmpty() const
{
	return mSize == 0;
}

/**
 * Retrieves the size of the list
 * @Return The list's size
 */
template <class T>
int SList<T>::size() const
{
	return mSize;
}

/**
 * Removes all items in the list
 */
template <class T>
void SList<T>::clear()
{
	auto current = mFront;
	while (current->next != nullptr)
	{
		auto temp = current;
		current = current->next;
		delete(temp);
	}
	mFront->mData = NULL;
	mSize = 0;
}

/**
 * Overrides the assignment operator to set the current list to another list of the same type
 */
template <class T>
T& SList<T>::operator=(T rhs)
{
	swap(rhs);
 	return *this;
}