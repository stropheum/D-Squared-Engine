#pragma once

template <class T>
SList<T>::Iterator::Iterator(SList<T>& owner, Node& node) :
	mOwner(owner), mNode(node) {}

