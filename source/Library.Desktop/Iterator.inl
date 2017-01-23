#pragma once

template <class T>
SList<T>::Iterator::Iterator(SList<T>* owner, Node* node) :
	mOwner(owner), mNode(node) {}

template <class T>
bool SList<T>::Iterator::operator==(Iterator& rhs)
{
	auto identicalOwners = (mOwner == rhs.mOwner);
	auto sameReference = mNode == rhs.mNode;
	return identicalOwners && sameReference;
}

template <class T>
bool SList<T>::Iterator::operator!=(Iterator& rhs)
{
	return !(this == &rhs);
}

template <class T>
void SList<T>::Iterator::operator++()
{
	// TODO get increment operator to stop breaking
	if (mNode != nullptr)
	{
		mNode = mNode->next;
	}
}

template <class T>
void SList<T>::Iterator::operator++(int)
{
	// TODO get increment operator to stop breaking
	++(*this);
}
