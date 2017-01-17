#pragma once
/**
* Default constructor
*/
template <class T>
SList<T>::SList() : mSize(0), mFront(nullptr), mBack(nullptr)
{
}

/**
* Copy Constructor
* Performs a deep copy of every current element in the list
*/
template <class T>
SList<T>::SList(const SList<T>& obj) : mSize(0), mFront(nullptr), mBack(nullptr)
{
	auto current = obj.mFront;
	if (current != nullptr)
	{
		while (current != nullptr)
		{
			pushBack(current->mData);
			current = current->next;
		}
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
T& SList<T>::front()
{
	return mFront->mData;
}

/**
* Retrieves the back item on the list
* @Return The templated item at the back of the list
*/
template <class T>
T& SList<T>::back()
{
	auto current = mFront;
	while (current->next != nullptr)
	{
		current = current->next;
	}
	return current->mData;
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
	if (current != nullptr)
	{
		while (current->next != nullptr)
		{
			auto temp = current;
			current = current->next;
			delete(temp);
		}
	}
	if (mFront != nullptr)
	{
		mFront->mData = NULL;
	}
	mSize = 0;
}

template <class T>
SList<T>& SList<T>::operator=(const SList<T>& rhs)
{
	if (this != &rhs)
	{
		clear();
		auto current = rhs.mFront;
		while (current != nullptr)
		{
			pushBack(current->mData);
			current = current->next;
		}
	}
	return *this;
}