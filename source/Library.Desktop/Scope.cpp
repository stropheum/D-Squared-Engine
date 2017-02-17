#include "pch.h"
#include "Scope.h"


namespace Library
{
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

	Datum* Scope::search(const std::string& key, Scope** parent)
	{
		UNREFERENCED_PARAMETER(parent);
		// TODO: Is parent necessary if i'm calling it recursively using mParent? Confused
		auto result = find(key);
		if (result == nullptr && mParent == nullptr) result = nullptr;
		if (result == nullptr && mParent != nullptr) result = mParent->search(key);
		return result;
	}

	Datum& Scope::append(const std::string& key)
	{
		auto found = mMap.find(key);
		if (found == mMap.end()) found = mMap.insert(std::pair<std::string, Datum>(key, Datum()));
		mVector.pushBack(&(*found).second);
		return (*found).second;
	}

	Scope& Scope::appendScope(const std::string& key)
	{
		auto found = find(key); // If that key exists, find it
		Scope* result = nullptr;
		
		if (found == nullptr)
		{
			Datum* child = &found->get<Scope*>(0)->append(key);
			child->setType(DatumType::Scope);
			result = child->get<Scope*>(0);
			adopt(*result, "lil' babby", 0); // TODO: Figure out how to properly call adopt
		}
		else
		{
			// Append scope to this scope, set its type and whatnot
		}
		
		return *result;
	}

	void Scope::adopt(Scope& child, const std::string& name, std::uint32_t index)
	{
		UNREFERENCED_PARAMETER(name);
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
		return *mVector[index];
	}

	bool Scope::operator==(const Scope& rhs) const
	{
		return mParent == rhs.mParent && mVector == rhs.mVector;
	}

	bool Scope::operator!=(const Scope& rhs) const
	{
		return !(operator==(rhs));
	}

	std::string Scope::findName(const Scope* scope)
	{
		UNREFERENCED_PARAMETER(scope);
		// TODO: Implement findName method
		return "Not Implemented yet";
	}

	std::string Scope::ToString() const
	{
		// TODO: Implement toString
		return "not implemented yet";
	}

	bool Scope::Equals(const RTTI* rhs) const
	{
		UNREFERENCED_PARAMETER(rhs);
		// TODO: Implement equals method
		return false;
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
