#include "pch.h"
#include "Scope.h"

namespace Library
{
	RTTI_DEFINITIONS(Library::Scope)

#pragma region Constructors/Destructor
		Scope::Scope(std::uint32_t capacity) :
		mMap(13), mVector(capacity), mParent(nullptr)
	{}

	Scope::Scope(const Scope& rhs):
		mMap(13), mVector(), mParent(nullptr)
	{
		operator=(rhs);
	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		for (std::uint32_t i = 0; i < rhs.mVector.size(); i++)
		{	
			auto& insertedPair = *mMap.insert(*rhs.mVector[i]);
			mVector.pushBack(&insertedPair);
		}
		return *this;
	}

	Scope::~Scope()
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

	void Scope::adopt(Scope& child, const std::string& key)
	{
		child.mParent = this;
		appendScope(key) = child;
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
