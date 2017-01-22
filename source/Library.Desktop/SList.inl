#pragma once

template <class T>
SList<T>::SList() : 
mSize(0), mFront(nullptr), mBack(nullptr), mBegin(this, mFront), mEnd(this, mBack) {}

template <class T>
SList<T>::SList(const SList<T>& obj) : 
	mSize(0), mFront(nullptr), mBack(nullptr), mBegin(this, mFront), mEnd(this, mBack)
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

template <class T>
void SList<T>::pushFront(T data)
{
	auto temp = mFront;
	mFront = new Node(data);
	mFront->next = temp;
	mSize++;
	if (mBack == nullptr)
	{
		mBack = mFront;
	}
}

template <class T>
void SList<T>::pushBack(T data)
{
	if (mFront == nullptr)
	{
		mFront = new Node(data);
		mBack = mFront;
	}
	else
	{
		auto current = mFront;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = new Node(data);
		mBack = current->next;
	}
	mSize++;
}

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
	mSize = 0;
}

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

template <class T>
T& SList<T>::front()
{
	return mFront->mData;
	//TODO: Throw exception if trying to call front on a null list
}

template <class T>
T& SList<T>::back()
{
	return mBack->mData;
	//TODO: Throw exception if trying to call back on a null list
}

template <class T>
bool SList<T>::isEmpty() const
{
	return mSize == 0;
}

template <class T>
int SList<T>::size() const
{
	return mSize;
}

template <class T>
typename SList<T>::Iterator& SList<T>::begin()
{
	return mBegin;
}

template <class T>
typename SList<T>::Iterator& SList<T>::end()
{
	return mEnd;
}