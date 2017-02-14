#include "pch.h"
#include "Scope.h"


namespace Library
{
#pragma region Constructors/Destructor
	Scope::Scope(std::uint32_t capacity)
	{
		UNREFERENCED_PARAMETER(capacity);
		// TODO: Implement constructor
	}

	Scope::Scope(const Scope& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		// TODO: Implement copy constructor
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
		UNREFERENCED_PARAMETER(key);
		// TODO: Implement find method
		return nullptr;
	}

	Datum* Scope::search(const std::string& key, Scope** scope)
	{
		UNREFERENCED_PARAMETER(key);
		UNREFERENCED_PARAMETER(scope);
		// TODO: Implement search method
		return nullptr;
	}

	/*Datum&*/void Scope::append(const std::string& key)
	{
		UNREFERENCED_PARAMETER(key);
		// TODO: Implement append method
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
