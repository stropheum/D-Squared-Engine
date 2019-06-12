#pragma once
#include <exception>


namespace Library
{
    template <typename T>
    SList<T>::SList() :
        m_size(0), m_front(nullptr), m_back(nullptr) {}

    template <typename T>
    SList<T>::~SList()
    {
        Node* current = m_front;
        while (current != nullptr)
        {
            Node* newCurrent = current->Next();
            delete(current);
            current = newCurrent;
        }
    }

    template <typename T>
    SList<T>::SList(const SList<T>& obj) :
        SList()
    {
        auto current = obj.m_front;
        while (current != nullptr)
        {
            PushBack(current->Data());
            current = current->Next();
        }
    }

    template <typename T>
    SList<T>& SList<T>::operator=(const SList<T>& rhs)
    {
        if (this != &rhs)
        {
            Clear();
            auto current = rhs.m_front;
            while (current != nullptr)
            {
                PushBack(current->Data());
                current = current->Next();
            }
        }
        return *this;
    }

    template <typename T>
    typename SList<T>::Iterator SList<T>::PushFront(const T& data)
    {
        auto temp = m_front;
        m_front = new Node(data);
        m_front->Next() = temp;
        m_size++;
        if (m_back == nullptr)
        {
            m_back = m_front;
            m_back->Next() = nullptr;
        }

        return Iterator(this, m_front);
    }

    template <typename T>
    typename SList<T>::Iterator SList<T>::PushBack(const T& data)
    {
        if (m_front == nullptr)
        {
            m_front = new Node(data);
            m_back = m_front;
            m_back->Next() = nullptr;
        }
        else
        {
            m_back->Next() = new Node(data);
            m_back = m_back->Next();
            m_back->Next() = nullptr;
        }

        m_size++;
        return Iterator(this, m_back);
    }

    template <typename T>
    void SList<T>::Clear()
    {
        auto current = m_front;
        if (current != nullptr)
        {
            while (current->Next() != nullptr)
            {
                auto temp = current;
                current = current->Next();
                delete(temp);
            }
        }
        m_size = 0;
    }

    template <typename T>
    T SList<T>::PopFront()
    {
        if (m_front == nullptr)
        {
            throw std::exception("Popping Front on null SList");
        }

        auto oldFront = m_front;
        auto result = m_front->Data();
        m_front = m_front->Next();
        delete(oldFront);
        m_size--;
        return result;
    }

    template <typename T>
    T& SList<T>::Front()
    {
        if (m_front == nullptr)
        {
            throw std::exception("SList is null");
        }
        return m_front->Data();
    }

    template <typename T>
    const T& SList<T>::Front() const
    {
        if (m_front == nullptr)
        {
            throw std::exception("SList is null");
        }
        return m_front->Data();
    }

    template <typename T>
    T& SList<T>::Back()
    {
        if (m_front == nullptr)
        {
            throw std::exception("List is null");
        }
        return m_back->Data();
    }

    template <typename T>
    const T& SList<T>::Back() const
    {
        if (m_front == nullptr)
        {
            throw std::exception("List is null");
        }
        return m_back->Data();
    }

    template <typename T>
    bool SList<T>::IsEmpty() const
    {
        return m_size == 0;
    }

    template <typename T>
    std::uint32_t SList<T>::Size() const
    {
        return m_size;
    }

    template <typename T>
    typename SList<T>::Iterator SList<T>::begin() const
    {
        return Iterator(const_cast<SList<T>* const>(this), m_front);
    }

    template <typename T>
    typename SList<T>::Iterator SList<T>::end() const
    {
        return Iterator(const_cast<SList<T>* const>(this), nullptr);
    }

    template <typename T>
    typename SList<T>::Iterator SList<T>::InsertAfter(const T& value, const Iterator& location)
    {
        if (location == this->end() || location.mNode == m_back)
        {
            PushBack(value);
            return Iterator(this, m_back);
        }

        for (Iterator iter = begin(); iter != end(); ++iter)
        {
            if (location == iter)
            {
                Node* temp = new Node(value);
                temp->Next() = location.mNode->Next();
                location.mNode->Next() = temp;
                return Iterator(this, temp);
            }
        }

        return end();
    }

    template <typename T>
    typename SList<T>::Iterator SList<T>::Find(const T& value) const
    {
        for (auto iter = begin(); iter != end(); ++iter)
        {
            if (*iter == value)
            {
                return iter;
            }
        }

        return end();
    }

    template <typename T>
    void SList<T>::Remove(const T& value)
    {
        if (m_front != nullptr && m_front->Data() == value)
        {
            Node* removeNode = m_front;
            m_front = m_front->Next();
            delete(removeNode);
            return;
        }

        Node* lastNode = nullptr;
        for (auto iter = begin(); iter != end(); ++iter)
        {
            if (lastNode != nullptr)
            {
                if (iter.mNode->Data() == value)
                {
                    lastNode->Next() = iter.mNode->Next();
                    delete(iter.mNode);
                    return;
                }
            }
            lastNode = iter.mNode;
        }
    }

    template <class T>
    SList<T>::Iterator::Iterator() :
        mOwner(nullptr), mNode(nullptr)
    {}

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
    typename SList<T>::Iterator& SList<T>::Iterator::operator++()
    {
        if (mNode != nullptr)
        {
            mNode = mNode->Next();
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
        if (mNode == nullptr)
        {
            throw std::exception("De-referencing nullptr on S-List iterator");
        }
        return mNode->Data();
    }
}