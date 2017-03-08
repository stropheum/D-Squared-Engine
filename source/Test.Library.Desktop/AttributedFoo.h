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

		AttributedFoo(const AttributedFoo& rhs);
		AttributedFoo& operator=(const AttributedFoo& rhs);

		AttributedFoo(const AttributedFoo&& rhs);
		AttributedFoo& operator=(const AttributedFoo&& rhs);
	
	private:
		void init();

	public:
		// Individual members
		std::int32_t mInt;
		float mFloat;
		glm::vec4 mVector;
		glm::mat4 mMatrix;
		std::string mString;
		Scope* mScope;
		
		// Array members
		std::int32_t* iArray;
		float* fArray;
		glm::vec4* vArray;
		glm::mat4* mArray;
		std::string* sArray;
	};
}


