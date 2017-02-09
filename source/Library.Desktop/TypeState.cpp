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

}
