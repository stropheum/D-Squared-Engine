#pragma once
#include "Datum.h"

namespace Library
{
	class TypeState
	{
	public:
		virtual ~TypeState();

		// Assignment operators
		virtual Datum& operator=(const std::int32_t& rhs);
		virtual Datum& operator=(const float& rhs);
		virtual Datum& operator=(const glm::vec4& rhs);
		virtual Datum& operator=(const glm::mat4& rhs);
		virtual Datum& operator=(const std::string& rhs);
		virtual Datum& operator=(Library::RTTI* const& rhs);

		virtual void setSize(std::uint32_t size);
		virtual void reserve(std::uint32_t capacity);
		virtual void clear();

	protected:
		TypeState(Datum* const context);
		Datum* mContext;
	};
}
