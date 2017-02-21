#include "pch.h"
#include "TypeState.h"

namespace Library
{
	TypeState::TypeState(Datum* const context):
		mContext(context)
	{}

	bool TypeState::operator==(const Datum& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		return false;
	}

	Datum& TypeState::operator=(const std::int32_t& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		throw std::exception("Invalid assignment operation");
	}

	Datum& TypeState::operator=(const float& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		throw std::exception("Invalid assignment operation");
	}

	Datum& TypeState::operator=(const glm::vec4& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		throw std::exception("Invalid assignment operation");
	}

	Datum& TypeState::operator=(const glm::mat4& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		throw std::exception("Invalid assignment operation");
	}

	Datum& TypeState::operator=(Scope* const rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		throw std::exception("Invalid assignment operation");
	}

	Datum& TypeState::operator=(const std::string& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		throw std::exception("Invalid assignment operation");
	}

	Datum& TypeState::operator=(Library::RTTI* const& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		throw std::exception("Invalid assignment operation");
	}

	void TypeState::clear()
	{	// Do nothing with clear if called from this context
	}

	void TypeState::setFromString(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
		throw std::exception("Attempting to set from storage on invalid type");
	}

	void TypeState::setStorage(const Datum& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		throw std::exception("Calling setStorage on Invalid type");
	}

	void TypeState::setStorage(std::int32_t* data, std::uint32_t size)
	{
		UNREFERENCED_PARAMETER(data);
		UNREFERENCED_PARAMETER(size);
		throw std::exception("Attempting to set storage on unknown type");
	}

	void TypeState::setStorage(float* data, std::uint32_t size)
	{
		UNREFERENCED_PARAMETER(data);
		UNREFERENCED_PARAMETER(size);
		throw std::exception("Attempting to set storage on unknown type");
	}

	void TypeState::setStorage(glm::vec4* data, std::uint32_t size)
	{
		UNREFERENCED_PARAMETER(data);
		UNREFERENCED_PARAMETER(size);
		throw std::exception("Attempting to set storage on unknown type");
	}

	void TypeState::setStorage(glm::mat4* data, std::uint32_t size)
	{
		UNREFERENCED_PARAMETER(data);
		UNREFERENCED_PARAMETER(size);
		throw std::exception("Attempting to set storage on unknown type");
	}

	void TypeState::setStorage(Scope** data, std::uint32_t size)
	{
		UNREFERENCED_PARAMETER(data);
		UNREFERENCED_PARAMETER(size);
		throw std::exception("Attempting to set storage on unknown type");
	}

	void TypeState::setStorage(std::string* data, std::uint32_t size)
	{
		UNREFERENCED_PARAMETER(data);
		UNREFERENCED_PARAMETER(size);
		throw std::exception("Attempting to set storage on unknown type");
	}

	void TypeState::setStorage(Library::RTTI** data, std::uint32_t size)
	{
		UNREFERENCED_PARAMETER(data);
		UNREFERENCED_PARAMETER(size);
		throw std::exception("Attempting to set storage on unknown type");
	}

	std::string TypeState::toString(std::uint32_t index)
	{
		UNREFERENCED_PARAMETER(index);
		return "";
	}
}
