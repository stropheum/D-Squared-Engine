#pragma once
#include <exception>

namespace Library
{
	template <typename T>
	SList<T>::SList() :
		mSize(0), mFront(nullptr), mBack(nullptr) {}

	template <typename T>
	SList<T>::SList(const SList<T>& obj) :
		SList()
	{
		auto current = obj.mFront;
		while (current != nullptr)
		{
			pushBack(current->mData);
			current = current->mNext;
		}
	}

	template <typename T>
	SList<T>& SList<T>::operator=(const SList<T>& rhs)
	{
		if (this != &rhs)
		{
			clear();
			auto current = rhs.mFront;
			while (current != nullptr)
			{
				pushBack(current->mData);
				current = current->mNext;
			}
		}
		return *this;
	}

	template <typename T>
	SList<T>::~SList()
	{
		Node* current = mFront;
		while (current != nullptr)
		{
			Node* newCurrent = current->mNext;
			delete(current);
			current = newCurrent;
		}
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::pushFront(const T& data)
	{
		auto temp = mFront;
		mFront = new Node(data);
		mFront->mNext = temp;
		mSize++;
		if (mBack == nullptr)
		{
			mBack = mFront;
			mBack->mNext = nullptr;
		}

		return Iterator(this, mFront);
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::pushBack(const T& data)
	{
		if (mFront == nullptr)
		{
			mFront = new Node(data);
			mBack = mFront;
			mBack->mNext = nullptr;
		}
		else
		{
			mBack->mNext = new Node(data);
			mBack = mBack->mNext;
			mBack->mNext = nullptr;
		}

		mSize++;
		return Iterator(this, mBack);
	}

	template <typename T>
	void SList<T>::clear()
	{
		auto current = mFront;
		if (current != nullptr)
		{
			while (current->mNext != nullptr)
			{
				auto temp = current;
				current = current->mNext;
				delete(temp);
			}
		}
		mSize = 0;
	}

	template <typename T>
	T SList<T>::popFront()
	{
		if (mFront == nullptr) { throw std::exception("Popping front on null SList"); }

		auto oldFront = mFront;
		auto result = mFront->mData;
		mFront = mFront->mNext;
		delete(oldFront);
		mSize--;
		return result;
	}

	template <typename T>
	T& SList<T>::front()
	{
		if (mFront == nullptr)
		{
			throw std::exception("SList is null");
		}
		return mFront->mData;
	}

	template <typename T>
	const T& SList<T>::front() const
	{
		if (mFront == nullptr)
		{
			throw std::exception("SList is null");
		}
		return mFront->mData;
	}

	template <typename T>
	T& SList<T>::back()
	{
		if (mFront == nullptr)
		{
			throw std::exception("List is null");
		}
		return mBack->mData;
	}

	template <typename T>
	const T& SList<T>::back() const
	{
		if (mFront == nullptr)
		{
			throw std::exception("List is null");
		}
		return mBack->mData;
	}

	template <typename T>
	bool SList<T>::isEmpty() const
	{
		return mSize == 0;
	}

	template <typename T>
	std::uint32_t SList<T>::size() const
	{
		return mSize;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::begin()
	{
		return Iterator(this, mFront);
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::end()
	{
		return Iterator(this, nullptr);
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::insertAfter(const T& value, const Iterator& location)
	{
		if (location == this->end() || location.mNode == mBack)
		{
			pushBack(value);
			return Iterator(this, mBack);
		}

		for (Iterator iter = begin(); iter != end(); ++iter)
		{
			if (location == iter)
			{
				Node* temp = new Node(value);
				temp->mNext = location.mNode->mNext;
				location.mNode->mNext = temp;
				return Iterator(this, temp);
			}
		}

		return end();
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::find(const T& value) 
	{
		for (auto iter = begin(); iter != end(); ++iter)
		{
			if (*iter == value) return iter;
		}
		return end();
	}

	template <typename T>
	void SList<T>::remove(T value)
	{
		if (mFront->mData == value)
		{
			Node* removeNode = mFront;
			mFront = mFront->mNext;
			delete(removeNode);
			return;
		}

		Node* lastNode = nullptr;
		for (auto iter = begin(); iter != end(); ++iter)
		{
			if (lastNode != nullptr)
			{
				if (iter.mNode->mData == value)
				{
					lastNode->mNext = iter.mNode->mNext;
					delete(iter.mNode);
					return;
				}
			}
			lastNode = iter.mNode;
		}
	}

	/// /////////////////////////////// ///
	///  SList Iterator implementation  ///
	/// /////////////////////////////// ///

	template <typename T>
	SList<T>::Iterator::Iterator(SList<T>* owner, Node* node) :
		mOwner(owner), mNode(node) {}

	template <typename T>
	SList<T>::Iterator::Iterator(const Iterator& rhs) :
		mOwner(rhs.mOwner), mNode(rhs.mNode) {}

	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator=(const Iterator& rhs)
	{
		mOwner = rhs.mOwner;
		mNode = rhs.mNode;
		return *this;
	}

	template <typename T>
	bool SList<T>::Iterator::operator==(const Iterator& rhs) const
	{
		auto bothNull = (mOwner == nullptr) && (rhs.mOwner == nullptr);
		auto identicalOwners = (mOwner == rhs.mOwner);
		auto sameReference = mNode == rhs.mNode;
		return bothNull || (identicalOwners && sameReference);
	}

	template <typename T>
	bool SList<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(this == &rhs);
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++()
	{
		if (mNode != nullptr)
		{
			mNode = mNode->mNext;
		}
		else
		{
			throw std::exception("Incrementing past the end of a Singly-Linked list");
		}
		return *this;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		Iterator copy(*this);
		operator++();
		return copy;
	}

	template <typename T>
	T& SList<T>::Iterator::operator*()
	{
		return mNode->mData;
	}
}
