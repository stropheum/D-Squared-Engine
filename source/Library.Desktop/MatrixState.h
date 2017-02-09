#pragma once
#include "TypeState.h"

namespace Library
{
	class MatrixState :
		public TypeState
	{
	public:
		MatrixState(Datum* const context);
		~MatrixState();

		Datum& operator=(const glm::mat4& rhs) override;

		void setSize(std::uint32_t size) override;
	};
}

