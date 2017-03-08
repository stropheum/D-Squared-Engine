#pragma once
#include <Attributed.h>
#define CLM_FORCE_CXX98
#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
#pragma warning(pop)

namespace Library
{
	class AttributedFoo : public Attributed
	{
	public:
		AttributedFoo();
		~AttributedFoo();

		void populate() override;

		// Individual members
		std::int32_t i;
		float f;
		glm::vec4 v;
		glm::mat4 m;
		std::string s;
		
		// Array members
//			std::int32_t* iArray;
//			float* fArray;
//			glm::vec4* vArray;
//			glm::mat4 mArray;
//			std::string* sArray;
	};
}


