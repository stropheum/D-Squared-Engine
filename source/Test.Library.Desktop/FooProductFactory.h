#pragma once
#include "Factory.h"
#include <cassert>
#include "RTTI.h"
#include "FooProduct.h"

namespace Library
{
	class FooProductFactory : public Factory<Library::RTTI>
	{
	public:
		FooProductFactory() { Factory::add(this); }
		virtual ~FooProductFactory() { Factory::remove(this); }
		
		virtual std::string className() const override
		{
			return "FooProductFactory";
		}
		
		virtual Library::RTTI* create() override
		{
			Library::RTTI* product = new FooProduct();
			assert(product != nullptr);
			return product;
		}
	};
}
