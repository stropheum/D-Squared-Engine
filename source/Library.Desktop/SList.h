#pragma once
#include "pch.h"

template <class T> class SList
{
public:
	SList();
	~SList();
	static int getData();
	void pushFront();
	void popFront();
	void pushBack();
	bool isEmpty();
	T front();
	T back();
	int size();
	void clear();
	T& operator=(T rhs);
};

/**
* Default constructor
*/
template <class T>
SList<T>::SList()
{

}

/**
* Deconstructor
*/
template <class T>
SList<T>::~SList()
{
}

/**
* Placeholder method to test library integration
* @Return Constant value 10
*/
//TODO: remove this method
template <class T>
int SList<T>::getData()
{
	return 10;
}

template <class T>
void SList<T>::pushFront()
{
	//TODO: implement method body
}

template <class T>
void SList<T>::popFront()
{
	//TODO: implement method body
}

template <class T>
void SList<T>::pushBack()
{
	//TODO: implement method body
}

template <class T>
bool SList<T>::isEmpty()
{
	//TODO: implement method body
	return true;
}

template <class T>
T SList<T>::front()
{
	//TODO: imlement method body
	return new T();
}

template <class T>
T SList<T>::back()
{
	//TODO: implement method body
	return new T();
}

template <class T>
int SList<T>::size()
{
	//TODO: implement method body
	return 0;
}

template <class T>
void SList<T>::clear()
{
	//TDOO: implement method body
}

template <class T>
T& SList<T>::operator=(T rhs)
{
	swap(rhs);
 	return *this;
}
