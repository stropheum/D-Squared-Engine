#pragma once
#include "Vector.h"
#include "HashMap.h"

namespace Library
{
	class Scope
	{
		typedef std::pair<const std::string, Datum> ScopePair;
	public:

#pragma region Constructors/Destructor
		/// Constructor
		/// @Param capacity: Initial capacity of the scope. Defaulted to 1
		Scope(std::uint32_t capacity = 1);
		/// Copy constructor
		/// @Param rhs: The Scope being copied
		Scope(const Scope& rhs);
		/// Move copy constructor
		/// @Param rhs: The Scope being copied
		Scope(const Scope&& rhs);
		/// Assignment operator
		/// Performs a deep copy of the specified Scope
		/// @Param rhs: The Scope being copied
		Scope& operator=(const Scope& rhs);
		/// Move assignment operator
		/// Performs a deep copy of the specified Scope
		/// @Param rhs: The Scope being copied
		Scope& operator=(const Scope&& rhs);
		/// Destructor
		~Scope();
#pragma endregion

		Datum* find(const std::string& key);
		Datum* search(const std::string& key, Scope** scope);
		/*Datum&*/void append(const std::string& key);
		Scope& appendScope(const std::string& key);
		void adopt(Scope& child, const std::string& name, std::uint32_t index);
		Scope* getParent();
		/*Datum&*/void operator[](const std::string& key);
		/*Datum&*/void operator[](const std::uint32_t index);
		bool operator==(const Scope& rhs);
		bool operator!=(const Scope& rhs);
		std::string findName(const Scope* scope);

	private:
		void clear();

		HashMap<std::string, Datum> mMap;
		Vector<ScopePair> mVector;
	};
}
