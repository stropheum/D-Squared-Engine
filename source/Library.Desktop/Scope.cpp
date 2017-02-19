#include "pch.h"
#include "Scope.h"

namespace Library
{
	RTTI_DEFINITIONS(Library::Scope)

#pragma region Constructors/Destructor
	Scope::Scope(std::uint32_t capacity):
		mMap(capacity), mParent(nullptr)
	{}

	Scope::Scope(const Scope& rhs):
		mMap(rhs.mMap), mParent(rhs.mParent)
	{
		// TODO: How to deep copy the HashMap and vector appropriately?
	}

	Scope::Scope(Scope&& rhs):
		mMap(rhs.mMap), mVector(rhs.mVector), mParent(rhs.mParent)
	{
		rhs.mMap.clear();
		rhs.mVector.clear();
		rhs.mParent = nullptr;
	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		// TODO: Implement assignment operator
		return *this;
	}

	Scope& Scope::operator=(Scope&& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		// TODO: Implement move assignment operator
		// TODO: Destroy rhs
		return *this;
	}

	Scope::~Scope()
	{
		// TODO: Implement destructor
	}
#pragma endregion

#pragma region Public Methods
	Datum* Scope::find(const std::string& key)
	{
		auto iter = mMap.find(key);
		Datum* result = (iter != mMap.end()) ? &(*iter).second : nullptr;
		return result;
	}

	Datum* Scope::search(const std::string& key, Scope** foundScope)
	{
		auto result = find(key);

		if(result == nullptr)
		{	// If we didn't find the key, search in parent if they exist
			result = (mParent != nullptr) ? mParent->search(key) : nullptr;
		}

		if (result != nullptr)
		{	// We found our value
			*foundScope = this;
		}

		return result;
	}

	Datum& Scope::append(const std::string& key)
	{
		auto found = mMap.find(key);
		if (found == mMap.end())
		{
			found = mMap.insert(std::pair<std::string, Datum>(key, Datum()));
		}
		mVector.pushBack(&(*found));
		return (*found).second;
	}

	Scope& Scope::appendScope(const std::string& key)
	{
		Datum* found = find(key);
		Scope* result = nullptr;

		if (found != nullptr)
		{
			result = new Scope();
			found->pushBack(result);
		}
		else
		{	
			// Append a new datum with the key and set its value to this scope (implicit type setting)
			auto datum = append(key) = this;  
			// set result equal to the address of the first scope value in the newly created datum
			result = &datum[0];
		}

		return *result;
	}

	void Scope::adopt(Scope& child, const std::string& key, std::uint32_t index)
	{
		UNREFERENCED_PARAMETER(key);
		UNREFERENCED_PARAMETER(index);
		child.mParent = this;
		// TODO: Figure out what to do with name and index
	}

	Scope* Scope::getParent()
	{
		return mParent;
	}

	Datum& Scope::operator[](const std::string& key)
	{
		return append(key);
	}

	Datum& Scope::operator[](const std::uint32_t index)
	{
		return mVector[index]->second;
	}

	bool Scope::operator==(const Scope& rhs) const
	{
		return mVector == rhs.mVector;
	}

	bool Scope::operator!=(const Scope& rhs) const
	{
		return !(operator==(rhs));
	}

	std::string Scope::findName(Scope* const scope) const
	{
		std::string result = "";

		for (std::uint32_t i = 0; i < mVector.size(); i++)
		{
			auto& foundDatum = mVector[i]->second;
			if (foundDatum.type() == DatumType::Scope)
			{	
				for (std::uint32_t j = 0; j < foundDatum.size(); j++)
				{	
					if (&foundDatum[j] == scope)
					{
						result = mVector[i]->first;
						break;
					}
				}
			}
		}

		if (!result.compare(""))
		{
			throw std::exception("Child not found in the specified scope");
		}

		return result;
	}

	std::string Scope::ToString() const
	{
		return "Scope";
	}

	bool Scope::Equals(const RTTI* rhs) const
	{
		return this == rhs;
	}

#pragma endregion

#pragma region Private Methods
	void Scope::clear()
	{
		mVector.~Vector();
		mMap.~HashMap();
	}
#pragma endregion
}
