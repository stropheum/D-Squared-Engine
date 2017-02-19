#pragma once
#include "Vector.h"
#include "HashMap.h"

namespace Library
{
	class Datum; /// forward declaration of Datum class

	class Scope : public RTTI
	{
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
		Scope(Scope&& rhs);
		/// Assignment operator
		/// Performs a deep copy of the specified Scope
		/// @Param rhs: The Scope being copied
		Scope& operator=(const Scope& rhs);
		/// Move assignment operator
		/// Performs a deep copy of the specified Scope
		/// @Param rhs: The Scope being copied
		Scope& operator=(Scope&& rhs);
		/// Destructor
		~Scope();
#pragma endregion

		Datum* find(const std::string& key);
		Datum* search(const std::string& key, Scope** scope = nullptr);
		Datum& append(const std::string& key);
		Scope& appendScope(const std::string& key);
		void adopt(Scope& child, const std::string& name, std::uint32_t index);
		Scope* getParent();
		Datum& operator[](const std::string& key);
		Datum& operator[](const std::uint32_t index);
		bool operator==(const Scope& rhs) const;
		bool operator!=(const Scope& rhs) const;
		std::string findName(const Scope* scope);

		/// RTTI methods
		std::string ToString() const override;
		bool Equals(const RTTI* rhs) const override;

	private:
		void clear();

		HashMap<const std::string, Datum> mMap;
		Vector<std::pair<std::string const, Datum>*> mVector;
		Scope* mParent;
	};
}
