#pragma once
#include <string>
#include "Foo.h"
#include <CppUnitTestAssert.h>

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> inline std::wstring ToString<Foo>(const Foo& t) 
			{ 
				RETURN_WIDE_STRING(t.getData()); 
			}
		}
	}
}
