#pragma once
#include "TypeState.h"

namespace Library
{
	class VectorState :
		public TypeState
	{
	public:
		VectorState(Datum* const context);
		~VectorState();

		Datum& operator=(const glm::vec4& rhs) override;

		void setSize(std::uint32_t size) override;
		void reserve(std::uint32_t capacity) override;
		void clear() override;
		void setFromString(const std::string& value, const std::uint32_t& index) override;
		void setStorage(const Datum& rhs) override;
		void setStorage(glm::vec4* data, std::uint32_t size) override;
	};
}