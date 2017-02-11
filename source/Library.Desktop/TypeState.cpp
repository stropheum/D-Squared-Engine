#include "pch.h"
#include "TypeState.h"

namespace Library
{
	TypeState::TypeState(Datum* const context):
		mContext(context)
	{}

	TypeState::~TypeState()
	{}

#pragma region Assignment Operators
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
#pragma endregion 

	void TypeState::setSize(std::uint32_t size)
	{
		UNREFERENCED_PARAMETER(size);
		throw std::exception("Calling set size on Datum with no type");
	}

	void TypeState::reserve(std::uint32_t capacity)
	{
		UNREFERENCED_PARAMETER(capacity);
		throw std::exception("Attempting to reserve size of unknown type");
	}

	void TypeState::clear()
	{
		throw std::exception("Attempting to call clear on an unspecified Datum");
	}

	void TypeState::setFromString(const std::string& value, const std::uint32_t& index)
	{
		UNREFERENCED_PARAMETER(value);
		UNREFERENCED_PARAMETER(index);
		throw std::exception("Attempting to call setFromString on unspecified Datum");
	}

	void TypeState::setStorage(const Datum& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		throw std::exception("Attempting to set external storage with no specified Datum type");
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
}
