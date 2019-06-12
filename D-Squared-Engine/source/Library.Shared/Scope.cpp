#include "pch.h"
#include "Scope.h"


using namespace std;

namespace Library
{
    RTTI_DEFINITIONS(Library::Scope)

#pragma region Constructors/Destructor

        Scope::Scope(const uint32_t& capacity) :
        m_map(13), m_vector(), m_parent(nullptr)
    {
        m_vector.Reserve(capacity);
    }

    Scope::Scope(const Scope& rhs) :
        m_map(13), m_vector(), m_parent(nullptr)
    {
        operator=(rhs);
    }

    Scope& Scope::operator=(const Scope& rhs)
    {
        if (this != &rhs)
        {
            Clear();

            m_vector.Reserve(rhs.m_vector.Size());

            for (auto& iter : rhs.m_vector)
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
                        Scope* scope = new Scope(existingDatum.Get<Scope>(i));
                        scope->m_parent = this;
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
        m_map(), m_vector(), m_parent(nullptr)
    {
        operator=(move(rhs));
    }

    Scope& Scope::operator=(Scope&& rhs) noexcept
    {
        if (this != &rhs)
        {
            Clear();
            m_map = move(rhs.m_map);
            m_vector = move(rhs.m_vector);
            m_parent = rhs.m_parent;
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

        if (m_map.Size() > 0)
        {
            auto iter = m_map.Find(key);
            result = (iter != m_map.end()) ? &(*iter).second : nullptr;
        }

        return result;
    }

    Datum* const Scope::Find(const string& key) const
    {
        auto iter = m_map.Find(key);
        Datum* const result = (iter != m_map.end()) ? &(*iter).second : nullptr;
        return result;
    }

    Datum* Scope::Search(const string& key, Scope** foundScope)
    {
        auto result = Find(key);

        if (result == nullptr)
        {	// If we didn't Find the key, Search in parent if they exist
            result = (m_parent != nullptr) ? m_parent->Search(key) : nullptr;
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
        auto iter = m_map.Insert(pair<string, Datum>(key, Datum()), found);

        if (!found)
        {
            m_vector.PushBack(iter);
        }
        auto& result = (*iter);
        return result.second;
    }

    Datum& Scope::Append(const string& key, bool& found)
    {
        bool datumFound;
        auto iter = m_map.Insert(pair<string, Datum>(key, Datum()), datumFound);
        found = datumFound;

        if (!datumFound)
        {
            m_vector.PushBack(iter);
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
            scope->m_parent = this;
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
            result->m_parent = this;
        }

        return *result;
    }

    void Scope::Adopt(Scope& child, const string& key)
    {
        bool found;
        Datum& datum = Append(key, found);
        datum.SetType(DatumType::Scope);
        if (child.m_parent != nullptr)
        {
            child.Orphan();
        }
        child.m_parent = this;
        datum.PushBack(&child);
    }

    Scope* Scope::GetParent() const
    {
        return m_parent;
    }

    Datum& Scope::operator[](const string& key)
    {
        return Append(key);
    }

    Datum& Scope::operator[](const uint32_t& index)
    {
        if (index >= m_vector.Size())
        {
            throw exception("Index out of bounds");
        }
        return m_vector[index]->second;
    }

    bool Scope::operator==(const Scope& rhs) const
    {
        bool result = false;

        if (m_vector.Size() == rhs.m_vector.Size())
        {	// If the sizes are not equal, the vectors are not equivalent
            result = true;

            for (uint32_t i = 0; i < m_vector.Size(); i++)
            {
                if (*m_vector[i] != *rhs.m_vector[i])
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

        for (uint32_t i = 0; i < m_vector.Size(); i++)
        {
            auto& foundPair = m_vector[i];
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
        return m_map.begin();
    }

    HashMap<const string, Datum>::Iterator Scope::end() const
    {
        return m_map.end();
    }

#pragma endregion

#pragma region Private Methods

    void Scope::Clear()
    {
        for (uint32_t i = 0; i < m_vector.Size(); i++)
        {	// Loop through vector searching for Scope types
            Datum& datum = m_vector[i]->second;
            if (datum.Type() == DatumType::Scope)
            {	// When a Scope Type is found, delete all scopes in the datum
                for (uint32_t j = 0; j < datum.Size(); j++)
                {
                    delete &datum[j];
                }
            }
        }

        m_vector.Clear();
        m_map.Clear();
        m_parent = nullptr;
    }

    void Scope::Orphan()
    {
        Scope* parent = GetParent();
        string key = parent->FindName(this);

        auto& parentVector = parent->m_vector;
        for (uint32_t i = 0; i < parentVector.Size(); i++)
        {	// Search the vector for the index that matches

            string pKey = parentVector[i]->first;
            if (pKey == key)
            {	// we found the index, so we're going to jam everything down
                parentVector.Remove(parentVector[i]);
            }
        }

        // Eliminate the key from the hashmap
        parent->m_map.Remove(key);

        m_parent = nullptr;
    }

#pragma endregion
}