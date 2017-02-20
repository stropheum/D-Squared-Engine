#pragma once
#include "Vector.h"
#include "HashMap.h"
#include "RTTI.h"

namespace Library
{
	class Datum; /// forward declaration of Datum class
	
	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Library::Scope, Library::RTTI);

#pragma region Constructors/Destructor
	public:

		/// Constructor
		/// @Param capacity: Initial capacity of the scope. Defaulted to 1
		Scope(std::uint32_t capacity = 1);
		/// Copy constructor
		/// @Param rhs: The Scope being copied

		Scope(const Scope& rhs);
		/// Assignment operator
		/// Performs a deep copy of the specified Scope
		/// @Param rhs: The Scope being copied
		Scope& operator=(const Scope& rhs);

		/// Destructor
		~Scope();
#pragma endregion

		/// Finds the Datum with the associated key in the Scope, if it exists
		/// @Param key: The key being used to search for the associated Datum
		/// @Return: The Datum associated with the key if it exists. Null pointer otherwise
		Datum* find(const std::string& key);

		/// Searches the Scope hierarchy for the specified key, if it exists
		/// @Param key: The key of the string, Datum pair being searched for
		/// @Param foundScope: The pointer to the Scope pointer that is found. Optionally included and set to the found scope if it exists
		/// @Return: A pointer to the Datum being searched for
		Datum* search(const std::string& key, Scope** scope = nullptr);

		/// Appends a new string, Datum pair to the Scope
		/// @Param key: The key associated with the new Datum object
		/// @Return: A reference to the newly created Datum
		Datum& append(const std::string& key);

		/// Appends a new scope to the current Scope hierarchy
		/// @Param key: The key of the new Scope being appended
		/// @Return: A reference to the newly appended Scope
		Scope& appendScope(const std::string& key);

		/// Adopts a Scope as a child of the current Scope
		/// @Param child: The Scope being adopted
		/// @Param key: The key associated with the child
		void adopt(Scope& child, const std::string& name);

		/// Accessor method for the parent of the current Scope
		/// @Return: A pointer to the parent of this Scope
		Scope* getParent();

		/// Index operator
		/// @Param key: The key being searched for. If the key isn't found, a new Datum is appended with that key
		/// @Return: A reference to the Datum found or appended with the associated key
		Datum& operator[](const std::string& key);

		/// Index operator
		/// @Param index: The index into the Vector of inserted pair pointers
		/// @Return: A reference to the Datum found with the associated index
		/// @Exception: Thrown if accessing beyond the vector's bounds
		Datum& operator[](const std::uint32_t index);

		/// Equality operator
		/// @Param rhs: The Scope object being compared against
		/// @Return: True if the Scopes are equivalent
		bool operator==(const Scope& rhs) const;

		/// Inequality operator
		/// @Param rhs: The Scope object being compared against
		/// @Return: True if the Scopes are not equivalent
		bool operator!=(const Scope& rhs) const;

		/// Finds the key associated with a Scope
		/// @Param scope: The Scope being used to search for the associated key
		/// @Return: The key associated with the Scope
		/// @Exception: Thrown if the Scope does not exist in the children
		std::string findName(Scope* const scope) const;

		/// String representation of the RTTI type
		/// @Return: The word "Scope"
		std::string ToString() const override;

		/// Comparison for RTTI pointers
		/// @Param rhs: The RTTI pointer being compared against
		/// @Return: True if the RTTI pointers are equivalent
		bool Equals(const RTTI* rhs) const override;

	private:

		/// Clears the Vector and HashMap of all values
		void clear();

		/// Removes the reference to the child from the parent, and eliminates the child's reference to its parent
		/// @Param child: The Scope pointer being orphaned
		void orphan(Scope* child);

		/// The HashMap that stores the true string, Datum pairs for Scope
		HashMap<const std::string, Datum> mMap;

		/// The Vector that stores pointers to every inserted pair for easy indexing
		Vector<HashMap<const std::string, Datum>::Iterator> mVector;

		/// The parent of this Scope. May be null if this is the top-level Scope
		Scope* mParent;
	};
}
