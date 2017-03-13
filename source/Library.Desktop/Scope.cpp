#include "pch.h"
#include "Scope.h"

namespace Library
{
	RTTI_DEFINITIONS(Library::Scope)

#pragma region Constructors/Destructor
		Scope::Scope(std::uint32_t capacity) :
		mMap(13), mVector(), mParent(nullptr)
	{
		mVector.reserve(capacity);
	}

	Scope::Scope(const Scope& rhs):
		mMap(13), mVector(), mParent(nullptr)
	{
		operator=(rhs);
	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		if (this != &rhs)
		{
			clear();

			mVector.reserve(rhs.mVector.size());

			for (auto& iter : rhs.mVector)
			{
				auto& existingPair = *iter;
				Datum& existingDatum = const_cast<Datum&>(existingPair.second);
				Datum& newDatum = append(existingPair.first);

				if (existingDatum.type() == DatumType::Scope)
				{
					newDatum.setType(DatumType::Scope);
					newDatum.reserve(existingDatum.size());

					for (uint32_t i = 0; i < existingDatum.size(); ++i)
					{
						Scope* scope = new Scope(*existingDatum.get<Scope*>(i));
						scope->mParent = this;
						newDatum.pushBack(scope);
					}
				}
				else
				{
					newDatum = existingDatum;
				}
			}
		}

		return *this;
	}

	Scope::~Scope()
	{
		clear();
	}
#pragma endregion

#pragma region Public Methods

	/// Finds the Datum with the associated key in the Scope, if it exists
	/// @Param key: The key being used to search for the associated Datum
	/// @Return: The Datum associated with the key if it exists. Null pointer otherwise
	Datum* Scope::find(const std::string& key)
	{
		auto iter = mMap.find(key);
		Datum* result = (iter != mMap.end()) ? &(*iter).second : nullptr;
		return result;
	}

	/// Finds the Datum with the associated key in the Scope, if it exists
	/// @Param key: The key being used to search for the associated Datum
	/// @Return: The Datum associated with the key if it exists. Null pointer otherwise
	Datum* const Scope::find(const std::string& key) const
	{
		auto iter = mMap.find(key);
		Datum* const result = (iter != mMap.end()) ? &(*iter).second : nullptr;
		return result;
	}

	/// Searches the Scope hierarchy for the specified key, if it exists
	/// @Param key: The key of the string, Datum pair being searched for
	/// @Param foundScope: The pointer to the Scope pointer that is found. Optionally included and set to the found scope if it exists
	/// @Return: A pointer to the Datum being searched for
	Datum* Scope::search(const std::string& key, Scope** foundScope)
	{
		auto result = find(key);

		if(result == nullptr)
		{	// If we didn't find the key, search in parent if they exist
			result = (mParent != nullptr) ? mParent->search(key) : nullptr;
		}

		if (result != nullptr && foundScope != nullptr)
		{	// We found our value
			*foundScope = this;
		}

		return result;
	}

	/// Appends a new string, Datum pair to the Scope
	/// @Param key: The key associated with the new Datum object
	/// @Return: A reference to the newly created Datum
	Datum& Scope::append(const std::string& key)
	{
		bool found = false;
		auto iter = mMap.insert(std::pair<std::string, Datum>(key, Datum()), found);

		if (!found)
		{
			mVector.pushBack(iter);
		}
		auto& result = (*iter);
		return result.second;
	}

	/// Appends a new string, Datum pair to the Scope
	/// @Param key: The key associated with the new Datum object
	/// @Param found: Output parameter to determine if the Datum was found
	/// @Return: A reference to the newly created Datum
	Datum& Scope::append(const std::string& key, bool& found)
	{
		bool datumFound;
		auto iter = mMap.insert(std::pair<std::string, Datum>(key, Datum()), datumFound);
		found = datumFound;

		if (!datumFound)
		{
			mVector.pushBack(iter);
		}
		auto& result = (*iter);
		return result.second;
	}

	/// Appends a new scope to the current Scope hierarchy
	/// @Param key: The key of the new Scope being appended
	/// @Return: A reference to the newly appended Scope
	Scope& Scope::appendScope(const std::string& key)
	{
//		bool scopeFound;
//		Datum& datum = append(key, scopeFound);
//
//		if (!scopeFound)
//		{
//			Scope* scope = new Scope();
//			scope->mParent = this;
//			datum = scope;
//			return *scope;
//		}
//		else
//		{
//			return datum[0];
//		}
		Datum* found = find(key);
		Scope* result = nullptr;

		if (found != nullptr)
		{	// We know the scope exists already, so push back another on the same key
			Scope* scope = new Scope();
			scope->mParent = this;
			found->pushBack(scope);
		}
		else
		{	
			// Append a new datum with the key and set its value to this scope (implicit type setting)
			Library::Datum& datum = append(key);
			datum = new Scope();
			datum = Library::DatumType::Scope;
			// set result equal to the address of the first scope value in the newly created datum
			result = &datum[0];
			result->mParent = this;
		}

		return *result;
	}

	/// Adopts a Scope as a child of the current Scope
	/// @Param child: The Scope being adopted
	/// @Param key: The key associated with the child
	void Scope::adopt(Scope& child, const std::string& key)
	{
		orphan(&child);
		auto& appended = appendScope(key);
		appended = child;
		child.mParent = this;
	}

	/// Accessor method for the parent of the current Scope
	/// @Return: A pointer to the parent of this Scope
	Scope* Scope::getParent()
	{
		return mParent;
	}

	/// Index operator
	/// @Param key: The key being searched for. If the key isn't found, a new Datum is appended with that key
	/// @Return: A reference to the Datum found or appended with the associated key
	Datum& Scope::operator[](const std::string& key)
	{
		return append(key);
	}

	/// Index operator
	/// @Param index: The index into the Vector of inserted pair pointers
	/// @Return: A reference to the Datum found with the associated index
	/// @Exception: Thrown if accessing beyond the vector's bounds
	Datum& Scope::operator[](const std::uint32_t index)
	{
		if (index >= mVector.size())
		{
			throw std::exception("Index out of bounds");
		}
		return mVector[index]->second;
	}

	/// Equality operator
	/// @Param rhs: The Scope object being compared against
	/// @Return: True if the Scopes are equivalent
	bool Scope::operator==(const Scope& rhs) const
	{
		bool result = false;

		if (mVector.size() == rhs.mVector.size())
		{	// If the sizes are not equal, the vectors are not equivalent
			result = true;

			for (std::uint32_t i = 0; i < mVector.size(); i++)
			{
				if (*mVector[i] != *rhs.mVector[i])
				{	// If we encounter a bad match, the vectors are not equivalent
					result = false;
					break;
				}
			}
		}
		
		return result;
	}

	/// Inequality operator
	/// @Param rhs: The Scope object being compared against
	/// @Return: True if the Scopes are not equivalent
	bool Scope::operator!=(const Scope& rhs) const
	{
		return !(operator==(rhs));
	}

	/// Finds the key associated with a Scope
	/// @Param scope: The Scope being used to search for the associated key
	/// @Return: The key associated with the Scope
	/// @Exception: Thrown if the Scope does not exist in the children
	std::string Scope::findName(Scope* const scope) 
	{
		std::string result = "";

		for (std::uint32_t i = 0; i < mVector.size(); i++)
		{
			auto& foundPair = mVector[i];
			if (foundPair->second.type() == DatumType::Scope)
			{	
				Scope* foundScope = nullptr;
				scope->search(foundPair->first, &foundScope);
				if (foundScope == scope)
				{
					result = foundPair->first;
				}
			}
		}

		if (!result.compare(""))
		{
			throw std::exception("Child not found in the specified scope");
		}

		return result;
	}

	/// String representation of the RTTI type
	/// @Return: The word "Scope"
	std::string Scope::ToString() const
	{
		return "Scope";
	}

	/// Comparison for RTTI pointers
	/// @Param rhs: The RTTI pointer being compared against
	/// @Return: True if the RTTI pointers are equivalent
	bool Scope::Equals(const RTTI* rhs) const
	{
		Scope* scope = rhs->As<Scope>();
		return (scope != nullptr) ? operator==(*scope) : false;
	}

#pragma endregion

#pragma region Private Methods

	/// Clears the Vector and HashMap of all values
	void Scope::clear()
	{	
		for (std::uint32_t i = 0; i < mVector.size(); i++)
		{	// Loop through vector searching for Scope types
			Datum& datum = mVector[i]->second;
			if (datum.type() == DatumType::Scope)
			{	// When a Scope type is found, delete all scopes in the datum
				for (std::uint32_t j = 0; j < datum.size(); j++)
				{
					delete &datum[j];
				}
			}
		}

		mVector.clear();
		mMap.clear();
		mParent = nullptr;
	}

	/// Removes the reference to the child from the parent, and eliminates the child's reference to its parent
	/// @Param child: The Scope pointer being orphaned
	void Scope::orphan(Scope* child)
	{
		if (child != nullptr)
		{
			Scope& parent = *child->getParent();
			if (&parent == this)
			{
				std::string key = parent.findName(child);
				parent[key].remove(child);
				child->mParent = nullptr;
			}
		}
	}

#pragma endregion
}
