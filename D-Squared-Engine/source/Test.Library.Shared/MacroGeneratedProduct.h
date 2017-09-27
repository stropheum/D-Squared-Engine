#pragma once
#include "RTTI.h"
#include "Factory.h"
#include <cassert>

namespace Library
{
	class MacroGeneratedProduct : public RTTI
	{
		RTTI_DECLARATIONS(MacroGeneratedProduct, RTTI)
	public:
		MacroGeneratedProduct();
		~MacroGeneratedProduct();
	};

	ConcreteFactory(RTTI, MacroGeneratedProduct)
}


