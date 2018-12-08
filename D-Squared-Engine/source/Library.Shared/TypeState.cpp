#include "pch.h"
#include "TypeState.h"


using namespace std;

namespace Library
{
    TypeState::TypeState(Datum& context) :
        mContext(context)
    {}

    bool TypeState::operator==(const Datum& rhs)
    {
        UNREFERENCED_PARAMETER(rhs);
        return false;
    }

    Datum& TypeState::operator=(const int32_t& rhs)
    {
        UNREFERENCED_PARAMETER(rhs);
        throw exception("Invalid assignment operation");
    }

    Datum& TypeState::operator=(const float& rhs)
    {
        UNREFERENCED_PARAMETER(rhs);
        throw exception("Invalid assignment operation");
    }

    Datum& TypeState::operator=(const glm::vec4& rhs)
    {
        UNREFERENCED_PARAMETER(rhs);
        throw exception("Invalid assignment operation");
    }

    Datum& TypeState::operator=(const glm::mat4x4& rhs)
    {
        UNREFERENCED_PARAMETER(rhs);
        throw exception("Invalid assignment operation");
    }

    Datum& TypeState::operator=(Scope* const rhs)
    {
        UNREFERENCED_PARAMETER(rhs);
        throw exception("Invalid assignment operation");
    }

    Datum& TypeState::operator=(const string& rhs)
    {
        UNREFERENCED_PARAMETER(rhs);
        throw exception("Invalid assignment operation");
    }

    Datum& TypeState::operator=(Library::RTTI* const& rhs)
    {
        UNREFERENCED_PARAMETER(rhs);
        throw exception("Invalid assignment operation");
    }

    void TypeState::Clear()
    {	// Do nothing with Clear if called from this context
    }

    void TypeState::SetFromString(const string& value, const uint32_t& index)
    {
        UNREFERENCED_PARAMETER(value);
        UNREFERENCED_PARAMETER(index);
        throw exception("Attempting to set from storage on invalid type");
    }

    void TypeState::SetStorage(const Datum& rhs)
    {
        UNREFERENCED_PARAMETER(rhs);
        throw exception("Calling SetStorage on Invalid type");
    }

    void TypeState::SetStorage(int32_t* data, const uint32_t& size)
    {
        UNREFERENCED_PARAMETER(data);
        UNREFERENCED_PARAMETER(size);
        throw exception("Attempting to set storage on unknown type");
    }

    void TypeState::SetStorage(float* data, const uint32_t& size)
    {
        UNREFERENCED_PARAMETER(data);
        UNREFERENCED_PARAMETER(size);
        throw exception("Attempting to set storage on unknown type");
    }

    void TypeState::SetStorage(glm::vec4* data, const uint32_t& size)
    {
        UNREFERENCED_PARAMETER(data);
        UNREFERENCED_PARAMETER(size);
        throw exception("Attempting to set storage on unknown type");
    }

    void TypeState::SetStorage(glm::mat4x4* data, const uint32_t& size)
    {
        UNREFERENCED_PARAMETER(data);
        UNREFERENCED_PARAMETER(size);
        throw exception("Attempting to set storage on unknown type");
    }

    void TypeState::SetStorage(Scope** data, const uint32_t& size)
    {
        UNREFERENCED_PARAMETER(data);
        UNREFERENCED_PARAMETER(size);
        throw exception("Attempting to set storage on unknown type");
    }

    void TypeState::SetStorage(string* data, const uint32_t& size)
    {
        UNREFERENCED_PARAMETER(data);
        UNREFERENCED_PARAMETER(size);
        throw exception("Attempting to set storage on unknown type");
    }

    void TypeState::SetStorage(Library::RTTI** data, const uint32_t& size)
    {
        UNREFERENCED_PARAMETER(data);
        UNREFERENCED_PARAMETER(size);
        throw exception("Attempting to set storage on unknown type");
    }

    string TypeState::ToString(const uint32_t& index)
    {
        UNREFERENCED_PARAMETER(index);
        return "";
    }
}