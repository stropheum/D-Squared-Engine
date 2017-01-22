#pragma once

template <class T>
SList<T>::Iterator::Iterator(SList<T>* owner, Node& node) :
	mOwner(owner), mNode(node) {}

template <class T>
bool SList<T>::Iterator::operator==(Iterator& rhs)
{
	return (
		(this == &rhs) &&
		(&mNode == &rhs.mNode));
}

template <class T>
bool SList<T>::Iterator::operator!=(Iterator& rhs)
{
	return !(this == &rhs);
}