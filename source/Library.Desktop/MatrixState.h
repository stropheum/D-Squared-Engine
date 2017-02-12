#pragma once
#include "TypeState.h"

namespace Library
{
	class MatrixState :
		public TypeState
	{
	public:
		explicit MatrixState(Datum* const context);

		Datum& operator=(const glm::mat4& rhs) override;

		void setSize(std::uint32_t size) override;
		void reserve(std::uint32_t capacity) override;
		void clear() override;
		void setFromString(const std::string& value, const std::uint32_t& index) override;
		void setStorage(const Datum& rhs) override;
		void setStorage(glm::mat4* data, std::uint32_t size) override;
		std::string toString(std::uint32_t index = 0) override;
	};
}

