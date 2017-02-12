#include "pch.h"
#include "TypeState.h"

namespace Library
{
	TypeState::TypeState(Datum* const context):
		mContext(context)
	{}

	TypeState::~TypeState()
	{}

	bool TypeState::operator==(const Datum& rhs)
	{
		UNREFERENCED_PARAMETER(rhs);
		throw std::exception("Invalid comparison");
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

	std::string TypeState::toString(std::uint32_t index)
	{
		UNREFERENCED_PARAMETER(index);
		throw std::exception("Attempting to call toString on unknown Datum type");
	}
}
