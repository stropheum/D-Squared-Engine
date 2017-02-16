#include "pch.h"
#include "Scope.h"


namespace Library
{
#pragma region Constructors/Destructor
	Scope::Scope(std::uint32_t capacity):
		mMap(capacity)
	{}

	Scope::Scope(const Scope& rhs):
		mMap(rhs.mMap)
	{
		// TODO: How to deep copy the hashmap and vector appropriately?
	}

	Scope::Scope(const Scope&& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		// TODO: Implement move copy constructor
		// TODO: Destroy rhs
	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		// TODO: Implement assignment operator
		return *this;
	}

	Scope& Scope::operator=(const Scope&& rhs)
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

	Datum* Scope::search(const std::string& key, Scope** scope)
	{
		UNREFERENCED_PARAMETER(key);
		UNREFERENCED_PARAMETER(scope);
		// TODO: Implement search method
		return nullptr;
	}

	Datum& Scope::append(const std::string& key)
	{
		auto found = mMap.find(key);
		if (found == mMap.end()) found = mMap.insert(std::pair<std::string, Datum>(key, Datum()));
		return (*found).second;
	}

	Scope& Scope::appendScope(const std::string& key)
	{
		UNREFERENCED_PARAMETER(key);
		// TODO: Implement appendScope
		return *this;
	}

	void Scope::adopt(Scope& child, const std::string& name, std::uint32_t index)
	{
		UNREFERENCED_PARAMETER(child);
		UNREFERENCED_PARAMETER(name);
		UNREFERENCED_PARAMETER(index);
		// TODO: Implement adopt method
	}

	Scope* Scope::getParent()
	{
		// TODO: Implement getParent
		return this;
	}

	/*Datum&*/void Scope::operator[](const std::string& key)
	{
		UNREFERENCED_PARAMETER(key);
//		return append(key);
	}

	/*Datum&*/void Scope::operator[](const std::uint32_t index)
	{
		UNREFERENCED_PARAMETER(index);
		// TODO: Implement operator[]
	}

	bool Scope::operator==(const Scope& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		// TODO: Implement operator==
		return false;
	}

	bool Scope::operator!=(const Scope& rhs)
	{
		return !(operator==(rhs));
	}

	std::string Scope::findName(const Scope* scope)
	{
		UNREFERENCED_PARAMETER(scope);
		// TODO: Implement findName method
		return "Not Implemented yet";
	}
#pragma endregion

#pragma region Private Methods
	void Scope::clear()
	{
		// TODO: Implement clear method
	}
#pragma endregion
}
