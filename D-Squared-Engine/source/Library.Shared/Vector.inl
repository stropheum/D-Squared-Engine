#pragma once
#include <new>
#include <cstdint>


namespace Library
{
    template <typename T>
    Vector<T>::Vector(bool fixedSize) :
        m_buffer(nullptr), m_size(0), m_capacity(CAPACITY_INCREMENT), m_fixedSize(fixedSize)
    {
        Reserve(m_capacity);
    }

    template <typename T>
    Vector<T>::~Vector()
    {
        Clear();
        free(m_buffer);
    }

    template <typename T>
    Vector<T>::Vector(const Vector<T>& rhs) :
        m_buffer(nullptr), m_size(0), m_capacity(rhs.m_capacity), m_fixedSize(rhs.m_fixedSize)
    {
        operator=(rhs);
    }

    template <typename T>
    Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
    {
        if (this != &rhs)
        {
            m_fixedSize = rhs.m_fixedSize;

            Clear();
            Reserve(rhs.m_capacity);
            if (rhs.m_size > 0)
            {
                for (auto iter = rhs.begin(); iter != rhs.end(); ++iter)
                {
                    PushBack(*iter);
                }
            }
        }
        return *this;
    }

    template <class T>
    Vector<T>::Vector(Vector<T>&& rhs) noexcept :
        m_buffer(nullptr), m_size(0), m_capacity(0), m_fixedSize(false)
    {
        operator=(std::move(rhs));
    }

    template <class T>
    Vector<T>& Vector<T>::operator=(Vector<T>&& rhs) noexcept
    {
        if (this != &rhs)
        {
            Clear();

            free(m_buffer);
            m_buffer = rhs.m_buffer;
            m_size = rhs.m_size;
            m_capacity = rhs.m_capacity;
            m_fixedSize = rhs.m_fixedSize;

            rhs.m_buffer = nullptr;
            rhs.m_size = 0;
            rhs.m_capacity = 0;
        }

        return *this;
    }

    template <typename T>
    bool Vector<T>::operator==(const Vector<T>& rhs) const
    {
        bool result = (m_size == rhs.m_size);

        if (result)
        { // If sizes are equal, compare further
            for (std::uint32_t i = 0; i < m_size; i++)
            {
                if (operator[](i) != rhs[i])
                {
                    result = false;
                }
            }
        }

        return result;
    }

    template <class T>
    bool Vector<T>::operator!=(const Vector<T>& rhs) const
    {
        return !(operator=(rhs));
    }

    template <typename T>
    typename Vector<T>::Iterator Vector<T>::Find(const T& value) const
    {
        for (Iterator iter = begin(); iter != end(); ++iter)
        {
            if (*iter == value) return iter;
        }
        return end();
    }

    template <typename T>
    typename Vector<T>::Iterator Vector<T>::begin() const
    {
        return Iterator::Iterator(this, 0);
    }

    template <typename T>
    typename Vector<T>::Iterator Vector<T>::end() const
    {
        return Iterator::Iterator(this, m_size);
    }

    template <typename T>
    T& Vector<T>::Front()
    {
        if (m_size == 0) throw std::exception("Calling Front on a null vector");
        return *m_buffer;
    }

    template <typename T>
    const T& Vector<T>::Front() const
    {
        if (m_size == 0) throw std::exception("Calling Front on a null vector");
        return const_cast<const T&>(*m_buffer);
    }

    template <typename T>
    T& Vector<T>::Back()
    {
        if (m_size == 0) throw std::exception("Calling Back on null vector");
        return *(m_buffer + (m_size - 1));
    }

    template <typename T>
    const T& Vector<T>::Back() const
    {
        if (m_size == 0) throw std::exception("Calling Back on a null vector");
        return *(m_buffer + (m_size - 1));
    }

    template <typename T>
    T& Vector<T>::At(const std::uint32_t& index)
    {
        return operator[](index);
    }

    template <typename T>
    const T& Vector<T>::At(const std::uint32_t& index) const
    {
        return const_cast<const T&>(operator[](index));
    }

    template <typename T>
    T& Vector<T>::operator[](const std::uint32_t& index)
    {
        if (index >= m_size) { throw std::exception("Index out of bounds"); }
        return *(m_buffer + index);
    }

    template <typename T>
    const T& Vector<T>::operator[](const std::uint32_t& index) const
    {
        if (m_buffer == nullptr) throw std::exception("Buffer is null");
        if (index >= m_size) throw std::exception("Index out of bounds");
        return const_cast<const T&>(*(m_buffer + index));
    }

    template <typename T>
    void Vector<T>::PopBack()
    {
        if (m_buffer == nullptr || m_size == 0) throw std::exception("Calling pop Back on an empty vector");
        m_buffer[m_size - 1].~T();
        --m_size;
    }

    template <typename T>
    std::uint32_t Vector<T>::Size() const
    {
        return m_size;
    }

    template <typename T>
    std::uint32_t Vector<T>::Capacity() const
    {
        return m_capacity;
    }

    template <typename T>
    bool Vector<T>::IsEmpty() const
    {
        return m_size == 0;
    }

    template <typename T>
    typename Vector<T>::Iterator Vector<T>::PushBack(const T& value)
    {
        typename Vector<T>::Iterator iter = end();
        if (!m_fixedSize)
        {
            if (m_size >= m_capacity) Reserve(m_capacity + CAPACITY_INCREMENT);
            new(m_buffer + m_size++) T(value);
            iter = Iterator(this, m_size - 1); // Reassign iter to point to last value pushed Back
        }
        return iter;
    }

    template <typename T>
    void Vector<T>::Reserve(std::uint32_t capacity)
    {
        if (capacity < m_size)
        {
            capacity = m_size;
        }

        T* temp = m_buffer;
        m_buffer = static_cast<T*>(malloc(sizeof(T) * capacity));
        if (m_size > 0) memcpy(m_buffer, temp, sizeof(T) * m_size);

        free(temp);
        m_capacity = capacity;
    }

    template <typename T>
    void Vector<T>::Clear()
    {
        if (m_buffer == nullptr)
        {
            return;
        }

        if (!IsEmpty())
        {
            while (m_size > 0)
            {
                PopBack();
            }
        }

        ShrinkToFit();
    }

    template <typename T>
    void Vector<T>::Remove(const T& value)
    {
        std::uint32_t firstValue = m_size;
        for (std::uint32_t i = 0; i < m_size; i++)
        {
            if (operator[](i) == value)
            {
                firstValue = i;
                break;
            }
        }

        // Destruct the value that we're about to squish
        if (firstValue != m_size) m_buffer[firstValue].~T();

        // Shift the entire buffer after the removed value down by 1 and decrement Size
        auto sizeToMove = (m_capacity * sizeof(T)) - (firstValue * sizeof(T));
        memmove(m_buffer + firstValue, m_buffer + firstValue + 1, sizeToMove);

        if (firstValue != m_size) --m_size;
    }

    template <class T>
    void Vector<T>::ShrinkToFit()
    {
        if (!m_fixedSize)
        {
            Reserve(m_size);
        }
    }


    template <typename T>
    Vector<T>::Iterator::Iterator() :
        m_owner(nullptr), m_index(0) {}

    template <typename T>
    Vector<T>::Iterator::Iterator(const Vector<T>* owner, const std::uint32_t& index) :
        m_owner(owner), m_index(index) {}

    template <typename T>
    Vector<T>::Iterator::Iterator(const Iterator& rhs) :
        m_owner(rhs.m_owner), m_index(rhs.m_index) {}

    template <typename T>
    bool Vector<T>::Iterator::operator==(const Iterator& rhs) const
    {
        return m_owner == rhs.m_owner && m_index == rhs.m_index;
    }

    template <typename T>
    bool Vector<T>::Iterator::operator!=(const Iterator& rhs) const
    {
        return !(operator==(rhs));
    }

    template <typename T>
    typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
    {
        if (m_owner == nullptr) { throw std::exception("Attempting to dereference nullptr"); }
        if (m_index > m_owner->Size()) { throw std::exception("Incrementing beyond vector bounds"); }

        if (m_index < m_owner->m_size)
        {
            m_index++;
        }

        return *this;
    }

    template <typename T>
    typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
    {
        Iterator result(m_index);
        operator++();
        return result;
    }

    template <typename T>
    T& Vector<T>::Iterator::operator*()
    {
        if (m_owner == nullptr) { throw std::exception("Owner is null"); }
        if (m_index > m_owner->Size()) { throw std::exception("Vector out of bounds"); }

        return const_cast<T&>(m_owner->operator[](m_index));
    }

    template <typename T>
    const T& Vector<T>::Iterator::operator*() const
    {
        if (m_owner == nullptr) { throw std::exception("Owner is null"); }
        if (m_index > m_owner->Size()) { throw std::exception("Vector out of bounds"); }

        return const_cast<T&>(m_owner->operator[](m_index));
    }

    template <typename T>
    typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& rhs)
    {
        if (*this != rhs)
        {
            m_owner = rhs.m_owner;
            m_index = rhs.m_index;
        }

        return *this;
    }
}