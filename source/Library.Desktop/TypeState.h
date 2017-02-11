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
		virtual void setFromString(const std::string& value, const std::uint32_t& index);
		
		virtual void setStorage(const Datum& rhs);
		virtual void setStorage(std::int32_t* data, std::uint32_t size);
		virtual void setStorage(float* data, std::uint32_t size);
		virtual void setStorage(glm::vec4* data, std::uint32_t size);
		virtual void setStorage(glm::mat4* data, std::uint32_t size);
		virtual void setStorage(std::string* data, std::uint32_t size);
		virtual void setStorage(Library::RTTI** data, std::uint32_t size);

	protected:
		TypeState(Datum* const context);
		Datum* mContext;
	};
}
