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
	};
}