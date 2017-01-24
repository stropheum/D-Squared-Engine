#pragma once

template <class T>
SList<T>::Iterator::Iterator(SList<T>* owner, Node* node) :
	mOwner(owner), mNode(node) {}

template <class T>
SList<T>::Iterator::Iterator(const Iterator& rhs) :
	mOwner(rhs.mOwner), mNode(rhs.mNode) {}

template <class T>
typename SList<T>::Iterator& SList<T>::Iterator::operator=(const Iterator& rhs)
{
	mOwner = rhs.mOwner;
	mNode = rhs.mNode;
	return *this;
}

template <class T>
bool SList<T>::Iterator::operator==(Iterator& rhs)
{
	auto bothNull = (mOwner == nullptr) && (rhs.mOwner == nullptr);
	auto identicalOwners = (mOwner == rhs.mOwner);
	auto sameReference = mNode == rhs.mNode;
	return bothNull || (identicalOwners && sameReference);
}

template <class T>
bool SList<T>::Iterator::operator!=(Iterator& rhs)
{
	return !(this == &rhs);
}

template <class T>
void SList<T>::Iterator::operator++()
{
	if (mNode != nullptr)
	{
		mNode = mNode->next;
	}
	else
	{
		throw std::exception("Incrementing past the end of a Singly-Linked list");
	}
}

template <class T>
void SList<T>::Iterator::operator++(int)
{
	++(*this);
}

template <class T>
T& SList<T>::Iterator::operator*()
{
	return mNode->mData;
}