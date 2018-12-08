#pragma once
#include "Vector.h"
#include "HashMap.h"
#include "RTTI.h"


namespace Library
{
    class Datum;

    class Scope : public RTTI
    {
        RTTI_DECLARATIONS(Library::Scope, Library::RTTI)

    public:

#pragma region Construction/Copy/Assignment

        explicit Scope(const std::uint32_t& capacity = 1);

        ~Scope();

        Scope(const Scope& rhs);

        Scope& operator=(const Scope& rhs);

        Scope(Scope&& rhs) noexcept;

        Scope& operator=(Scope&& rhs) noexcept;

#pragma endregion

        /**
         * Finds the Datum with the associated key in the Scope, if it exists
         * @Param key: The key being used to Search for the associated Datum
         * @Return: The Datum associated with the key if it exists. Null pointer otherwise
         */
        Datum* Find(const std::string& key);

        /**
         * Finds the Datum with the associated key in the Scope, if it exists
         * @Param key: The key being used to Search for the associated Datum
         * @Return: The Datum associated with the key if it exists. Null pointer otherwise
         */
        Datum* const Find(const std::string& key) const;

        /**
         * Searches the Scope hierarchy for the specified key, if it exists
         * @Param key: The key of the string, Datum pair being searched for
         * @Param foundScope: The pointer to the Scope pointer that is found. Optionally included and Set to the found scope if it exists
         * @Return: A pointer to the Datum being searched for
         */
        Datum* Search(const std::string& key, Scope** scope = nullptr);

        /**
         * Appends a new string, Datum pair to the Scope
         * @Param key: The key associated with the new Datum object
         * @Return: A reference to the newly created Datum
         */
        Datum& Append(const std::string& key);

        /**
         * Appends a new string, Datum pair to the Scope
         * @Param key: The key associated with the new Datum object
         * @Param found: Output parameter to determine if the Datum was found
         * @Return: A reference to the newly created Datum
         */
        Datum& Append(const std::string& key, bool& found);

        /**
         * Appends a new scope to the current Scope hierarchy
         * @Param key: The key of the new Scope being appended
         * @Return: A reference to the newly appended Scope
         */
        Scope& AppendScope(const std::string& key);

        /**
         * Adopts a Scope as a child of the current Scope
         * @Param child: The Scope being adopted
         * @Param key: The key associated with the child
         */
        void Adopt(Scope& child, const std::string& name);

        /**
         * Accessor method for the parent of the current Scope
         * @Return: A pointer to the parent of this Scope
         */
        Scope* GetParent() const;

        /**
         * Index operator
         * @Param key: The key being searched for. If the key isn't found, a new Datum is appended with that key
         * @Return: A reference to the Datum found or appended with the associated key
         */
        Datum& operator[](const std::string& key);

        /**
         * Index operator
         * @Param index: The index into the Vector of inserted pair pointers
         * @Return: A reference to the Datum found with the associated index
         * @Exception: Thrown if accessing beyond the vector's bounds
         */
        Datum& operator[](const std::uint32_t& index);

        /**
         * Equality operator
         * @Param rhs: The Scope object being compared against
         * @Return: True if the Scopes are equivalent
         */
        bool operator==(const Scope& rhs) const;

        /**
         * Inequality operator
         * @Param rhs: The Scope object being compared against
         * @Return: True if the Scopes are not equivalent
         */
        bool operator!=(const Scope& rhs) const;

        /**
         * Finds the key associated with a Scope
         * @Param scope: The Scope being used to Search for the associated key
         * @Return: The key associated with the Scope
         * @Exception: Thrown if the Scope does not exist in the children
         */
        std::string FindName(Scope* const scope);

        /**
         * String representation of the RTTI Type
         * @Return: The word "Scope"
         */
        std::string ToString() const override;

        /**
         * Comparison for RTTI pointers
         * @Param rhs: The RTTI pointer being compared against
         * @Return: True if the RTTI pointers are equivalent
         */
        bool Equals(const RTTI* rhs) const override;

        /**
         * Accesses the begin iterator for the undrlying hashmap
         * @Return: An iterator pointing to the beginning of the hashmap
         */
        HashMap<const std::string, Datum>::Iterator begin() const;

        /**
         * Accesses the end iterator for the undrlying hashmap
         * @Return: An iterator pointing to the end of the hashmap
         */
        HashMap<const std::string, Datum>::Iterator end() const;

    private:

        /**
         * Clears the Vector and HashMap of all values
         */
        void Clear();

        /**
         * Removes the reference to the child from the parent, and eliminates the child's reference to its parent
         */
        void Orphan();

    protected:

        // The HashMap that stores the true string, Datum pairs for Scope
        HashMap<const std::string, Datum> mMap;

        // The Vector that stores pointers to every inserted pair for easy indexing
        Vector<HashMap<const std::string, Datum>::Iterator> mVector;

        // The parent of this Scope. May be null if this is the top-level Scope
        Scope* mParent;

    };
}