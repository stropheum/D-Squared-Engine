#pragma once
#include <cstdint>


namespace Library
{
    /**
     * @Class Vector: A templated dynamically allocated array
     * @Author: Dale Diaz
     *
     * An implementation of vector which lazily loads memory as needed. Default
     * Capacity is 10 elements, but can be resized manually and shrunk to fit
     * the current data Set. Iterators are used to increment over the data without
     * causing any memory corruption
     */
    template <class T> class Vector
    {

    public:

        class Iterator;

#pragma region Construction/Copy/Assignment

        explicit Vector(bool fixedSize = false);

        ~Vector();

        Vector(const Vector<T>& rhs);

        Vector<T>& operator=(const Vector<T>& rhs);

        Vector(Vector<T>&& rhs) noexcept;

        Vector<T>& operator=(Vector<T>&& rhs) noexcept;

#pragma endregion

        /**
         * Comparison operator
         * @Param rhs: Vector being compared against
         */
        bool operator==(const Vector<T>& rhs) const;

        /**
         * Negated comparison operator
         * @Param rhs: Vector being compared against
         */
        bool operator!=(const Vector<T>& rhs) const;

        /**
         * Finds a value in the Vector, if it exists
         * @Param value: Value being searched for
         * @Return: An iterator pointing to the value if it exists, end() otherwise
         */
        Iterator Find(const T& value) const;

        /**
         * Begins iterating over the vector's data, starting At the first index
         * @Return: An iterator pointing to the first element in the Vector
         */
        Iterator begin() const;

        /**
         * A reference to the end of the vector, which has the meaning of "one past the end of the vector"
         * @return: An iterator pointing past the last element in the Vector
         */
        Iterator end() const;

        /**
         * The Front value in the Vector
         * @Return: A reference to the first element in the Vector
         * @Exception: Thrown if calling Front on an empty Vector
         */
        T& Front();

        /**
         * The Front value in the Vector
         * @Return: A const reference to the first element in the Vector
         * @Exception: Thrown if calling Front on an empty Vector
         */
        const T& Front() const;

        /**
         * The Back value in the Vector
         * @Return: A reference to the last element in the Vector
         * @Exception: Thrown if calling Back on an empty Vector
         */
        T& Back();

        /**
         * The Back value in the Vector
         * @Return: A const reference to the last element in the Vector
         * @Exception: Thrown if calling Back on an empty Vector
         */
        const T& Back() const;

        /**
         * Searches for an element in the Vector by index
         * @Param index: The index being retrieved
         * @Return: A reference to the element At the specified index
         * @Exception: Thrown if index is greater than or equal to Size
         */
        T& At(const std::uint32_t& index);

        /**
         * Searches for an element in the vector by index
         * @Param index: The index being retrieved
         * @Return: A const reference to the element At the specified index
         * @Exception: Thrown if index is greater than or equal to Size
         */
        const T& At(const std::uint32_t& index) const;

        /**
         * Searches for an element in the Vector by index
         * @Param index: The index being retrieved
         * @Return: A reference to the element At the specified index. Throws exception if out of bounds
         * @Exception: Thrown if accessing an index greater than or equal to Size
         */
        T& operator[](const std::uint32_t& index);

        /**
         * Const version of the index operator
         * @Param index: The index being retrieved
         * @Return: A const reference to the element At the specified index. Throws exception if out of bounds
         * @Exception: Thrown if accessing an index greater than or equal to Size
         */
        const T& operator[](const std::uint32_t& index) const;

        /**
         * removes the last element pushed to the Back of the Vector
         * @Exception: Thrown if calling pop Back on an empty Vector
         */
        void PopBack();

        /**
         * The current number of elements in the Vector
         * @Return: The current number of elements in the Vector
         */
        std::uint32_t Size() const;

        /**
         * The current number of spaces in the Vector that memory has been allocated for
         * @Return: The current number of allocated positions for data
         */
        std::uint32_t Capacity() const;

        /**
         * Method to assert if the Vector has zero elements in it
         * @Return: True if there are zero elements in Vector
         */
        bool IsEmpty() const;

        /**
         * Adds an element to the first empty index available
         * If there is no available Capacity, Reserve is called with 10 additional elements
         * @Param value: The value being added to the Vector
         */
        Iterator PushBack(const T& value);

        /**
         * Reserves space in the Vector for more elements
         * @Param Capacity: The new Capacity of the Vector
         * If Capacity is less then current Capacity, Capacity is shrunk to the new Size
         * If Capacity is less than current Size, Capacity is clamped to Size
         */
        void Reserve(std::uint32_t capacity);

        /**
         * Removes all elements from the Vector, sets Size and Capacity to zero and frees all memory
         */
        void Clear();

        /**
         * Removes the first instance of a value from the Vector
         * @Param value: The value being removed from the Vector
         * If value does not exist, nothing happens
         */
        void Remove(const T& value);

        /**
         * Clamps the Capacity to the Vector's current number of elements
         */
        void ShrinkToFit();

    private:
        T* m_buffer; // The space where elements will be stored
        std::uint32_t m_size; // The number of elements in the Vector
        std::uint32_t m_capacity; // The number of elements memory has been allocated for
        bool m_fixedSize; // Value to determine if the vector can be resized
        static const std::uint32_t CAPACITY_INCREMENT = 10; // Standard Reserve value increment

    public:
        class Iterator
        {
            friend class Vector;
        public:

            /**
             * Default constructor
             */
            Iterator();

            /**
             * Copy constructor
             * @Param rhs: The Iterator being copied
             */
            Iterator(const Iterator& rhs);

            /**
             * Assignment operator
             * @Param rhs: The Iterator being copied
             */
            Iterator& operator=(const Iterator& rhs);

            /**
             * Equality comparison operator
             * @Param rhs: The Iterator which is being compared against
             * @Return: True if both iterators are equivalent
             */
            bool operator==(const Iterator& rhs) const;

            /**
             * Not equal comparison operator
             * @Param rhs: The Iterator which is being compared against
             * @Return: True if the iterators are not equivalent
             */
            bool operator!=(const Iterator& rhs) const;

            /**
             * Increment operator(prefix)
             * @Return: Current iterator after increment has occurred
             * @Exception: Thrown if incrementing beyond vector bounds
             */
            Iterator& operator++();

            /**
             * Increment operator(postfix)
             * @Return: Copy of iterator before increment has occurred
             */
            Iterator operator++(int);

            /**
             * Dereference operator
             * @Return: A reference to the value pointed At by the Iterator
             * @Exception: Thrown if dereferencing a null value
             */
            T& operator*();

            const T& operator*() const;

        private:

            /**
             * Internal Iterator constructor
             * @Param owner: The Vector that owns this Iterator object
             * @Param index: The location that this iterator points to
             */
            Iterator(const Vector<T>* owner, const std::uint32_t& index);

            const Vector<T>* m_owner; // The vector that owns this Iterator
            std::uint32_t m_index; // The location that this iterator points to
        };
    };
}

#include "Vector.inl"