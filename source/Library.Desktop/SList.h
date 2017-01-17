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
	explicit SList(const SList<T>& obj);
	~SList();
	void pushFront(T data);
	void pushBack(T data);
	T popFront();
	T& front();
	T& back();
	bool isEmpty() const;
	int size() const;
	void clear();
	SList<T>& operator=(const SList<T>& rhs);
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

#include "SList.inl"
