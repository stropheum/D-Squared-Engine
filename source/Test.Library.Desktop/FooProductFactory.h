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
		FooProductFactory() { Add(this); }
		~FooProductFactory() { Remove(this); }
		
		virtual std::string ClassName() const override
		{
			return "FooProduct";
		}
		
		virtual Library::RTTI* Create() override
		{
			Library::RTTI* product = new FooProduct();
			assert(product != nullptr);
			return product;
		}
	};

	class BarProductFactory final : public Factory<Library::RTTI>
	{
	public:
		BarProductFactory() { Add(this); }
		~BarProductFactory() { Remove(this); }

		virtual std::string ClassName() const override
		{
			return "BarProduct";
		}

		virtual Library::RTTI* Create() override
		{
			Library::RTTI* product = new BarProduct();
			assert(product != nullptr);
			return product;
		}
	};
}
