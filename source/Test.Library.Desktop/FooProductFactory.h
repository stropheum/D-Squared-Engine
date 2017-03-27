#pragma once
#include "Factory.h"
#include <cassert>
#include "RTTI.h"
#include "FooProduct.h"

namespace Library
{
	class FooProductFactory final : public Factory<Library::RTTI>
	{
	public:
		FooProductFactory() { add(this); }
		~FooProductFactory() { remove(this); }
		
		virtual std::string className() const override
		{
			return "FooProduct";
		}
		
		virtual Library::RTTI* create() override
		{
			Library::RTTI* product = new FooProduct();
			assert(product != nullptr);
			return product;
		}
	};

	class BarProductFactory final : public Factory<Library::RTTI>
	{
	public:
		BarProductFactory() { add(this); }
		~BarProductFactory() { remove(this); }

		virtual std::string className() const override
		{
			return "BarProduct";
		}

		virtual Library::RTTI* create() override
		{
			Library::RTTI* product = new BarProduct();
			assert(product != nullptr);
			return product;
		}
	};
}
