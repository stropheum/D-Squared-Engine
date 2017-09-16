#include "pch.h"
#include "Scope.h"


using namespace std;

namespace Library
{
	RTTI_DEFINITIONS(Library::Scope)

#pragma region Constructors/Destructor

	Scope::Scope(const uint32_t& capacity) :
		mMap(13), mVector(), mParent(nullptr)
	{
		mVector.Reserve(capacity);
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
			Clear();

			mVector.Reserve(rhs.mVector.Size());

			for (auto& iter : rhs.mVector)
			{
				auto& existingPair = *iter;
				Datum& existingDatum = const_cast<Datum&>(existingPair.second);
				Datum& newDatum = Append(existingPair.first);

				if (existingDatum.Type() == DatumType::Scope)
				{
					newDatum.SetType(DatumType::Scope);
					newDatum.Reserve(existingDatum.Size());

					for (uint32_t i = 0; i < existingDatum.Size(); ++i)
					{
						Scope* scope = new Scope(*existingDatum.Get<Scope*>(i));
						scope->mParent = this;
						newDatum.PushBack(scope);
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

	Scope::Scope(Scope&& rhs) noexcept :
		mMap(), mVector(), mParent(nullptr)
	{
		operator=(move(rhs));
	}

	Scope& Scope::operator=(Scope&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();
			mMap = move(rhs.mMap);
			mVector = move(rhs.mVector);
			mParent = rhs.mParent;
		}
		
		return *this;
	}

	Scope::~Scope()
	{
		Clear();
	}

#pragma endregion

#pragma region Public Methods

	Datum* Scope::Find(const string& key)
	{
		Datum* result = nullptr;

		if (mMap.Size() > 0)
		{
			auto iter = mMap.Find(key);
			result = (iter != mMap.end()) ? &(*iter).second : nullptr;
		}

		return result;
	}

	Datum* const Scope::Find(const string& key) const
	{
		auto iter = mMap.Find(key);
		Datum* const result = (iter != mMap.end()) ? &(*iter).second : nullptr;
		return result;
	}

	Datum* Scope::Search(const string& key, Scope** foundScope)
	{
		auto result = Find(key);

		if(result == nullptr)
		{	// If we didn't Find the key, Search in parent if they exist
			result = (mParent != nullptr) ? mParent->Search(key) : nullptr;
		}

		if (result != nullptr && foundScope != nullptr)
		{	// We found our value
			*foundScope = this;
		}

		return result;
	}

	Datum& Scope::Append(const string& key)
	{
		bool found = false;
		auto iter = mMap.Insert(pair<string, Datum>(key, Datum()), found);

		if (!found)
		{
			mVector.PushBack(iter);
		}
		auto& result = (*iter);
		return result.second;
	}

	Datum& Scope::Append(const string& key, bool& found)
	{
		bool datumFound;
		auto iter = mMap.Insert(pair<string, Datum>(key, Datum()), datumFound);
		found = datumFound;

		if (!datumFound)
		{
			mVector.PushBack(iter);
		}
		auto& result = (*iter);
		return result.second;
	}

	Scope& Scope::AppendScope(const string& key)
	{
		Datum* found = Find(key);
		Scope* result = nullptr;

		if (found != nullptr)
		{	// We know the scope exists already, so push Back another on the same key
			Scope* scope = new Scope();
			scope->mParent = this;
			found->PushBack(scope);
		}
		else
		{	
			// Append a new datum with the key and Set its value to this scope (implicit Type setting)
			Library::Datum& datum = Append(key);
			datum = new Scope();
			datum = Library::DatumType::Scope;
			// Set result equal to the address of the first scope value in the newly created datum
			result = &datum[0];
			result->mParent = this;
		}

		return *result;
	}

	void Scope::Adopt(Scope& child, const string& key)
	{
		bool found;
		Datum& datum = Append(key, found);
		datum.SetType(DatumType::Scope);
		if (child.mParent != nullptr)
		{
			child.Orphan();
		}
		child.mParent = this;
		datum.PushBack(&child);
	}

	Scope* Scope::GetParent() const
	{
		return mParent;
	}

	Datum& Scope::operator[](const string& key)
	{
		return Append(key);
	}

	Datum& Scope::operator[](const uint32_t& index)
	{
		if (index >= mVector.Size())
		{
			throw exception("Index out of bounds");
		}
		return mVector[index]->second;
	}

	bool Scope::operator==(const Scope& rhs) const
	{
		bool result = false;

		if (mVector.Size() == rhs.mVector.Size())
		{	// If the sizes are not equal, the vectors are not equivalent
			result = true;

			for (uint32_t i = 0; i < mVector.Size(); i++)
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

	bool Scope::operator!=(const Scope& rhs) const
	{
		return !(operator==(rhs));
	}

	string Scope::FindName(Scope* const scope) 
	{
		string result = "";

		for (uint32_t i = 0; i < mVector.Size(); i++)
		{
			auto& foundPair = mVector[i];
			if (foundPair->second.Type() == DatumType::Scope)
			{	
				Scope* foundScope = nullptr;
				scope->Search(foundPair->first, &foundScope);
				if (foundScope == scope)
				{
					result = foundPair->first;
				}
			}
		}

		if (!result.compare(""))
		{
			throw exception("Child not found in the specified scope");
		}

		return result;
	}

	string Scope::ToString() const
	{
		return "Scope";
	}

	bool Scope::Equals(const RTTI* rhs) const
	{
		Scope* scope = rhs->As<Scope>();
		return (scope != nullptr) ? operator==(*scope) : false;
	}

	HashMap<const string, Datum>::Iterator Scope::begin() const
	{
		return mMap.begin();
	}

	HashMap<const string, Datum>::Iterator Scope::end() const
	{
		return mMap.end();
	}

#pragma endregion

#pragma region Private Methods

	void Scope::Clear()
	{	
		for (uint32_t i = 0; i < mVector.Size(); i++)
		{	// Loop through vector searching for Scope types
			Datum& datum = mVector[i]->second;
			if (datum.Type() == DatumType::Scope)
			{	// When a Scope Type is found, delete all scopes in the datum
				for (uint32_t j = 0; j < datum.Size(); j++)
				{
					delete &datum[j];
				}
			}
		}

		mVector.Clear();
		mMap.Clear();
		mParent = nullptr;
	}

	void Scope::Orphan()
	{
		Scope* parent = GetParent();
		string key = parent->FindName(this);
		
		auto& parentVector = parent->mVector;
		for (uint32_t i = 0; i < parentVector.Size(); i++)
		{	// Search the vector for the index that matches

			string pKey = parentVector[i]->first;
			if (pKey == key)
			{	// we found the index, so we're going to jam everything down
				parentVector.Remove(parentVector[i]);
			}
		}

		// Eliminate the key from the hashmap
		parent->mMap.Remove(key);

		mParent = nullptr;
	}

#pragma endregion
}
