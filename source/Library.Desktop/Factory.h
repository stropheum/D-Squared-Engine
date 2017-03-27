#pragma once
#include "HashMap.h"

namespace Library
{
	template <class AbstractProduct> class Factory
	{
#pragma region Abstract base class API

#pragma region ConcreteFactory Macro

		/// Macro used to generate factories for concrete products. 
		/// This macro should be put in the header file of any class 
		/// that wishes to have an associated factory
#define ConcreteFactory(AbstractProduct, ConcreteProduct)				\
	class ConcreteProduct##Factory : public Factory<AbstractProduct>	\
	{																	\
	public:																\
		ConcreteProduct##Factory() { add(this); }						\
		~ConcreteProduct##Factory() { remove(this); }					\
																		\
		virtual std::string className() const override					\
		{																\
			return #ConcreteProduct;									\
		}																\
																		\
		virtual Library::RTTI* create() override						\
		{																\
			AbstractProduct* product = new ConcreteProduct();			\
			assert(product != nullptr);									\
			return product;												\
		}																\
	};																	\

#pragma endregion

	public:

		/// Constructor
		Factory() {};

		/// Virtual destructor
		virtual ~Factory() = default;

		/// Class name accessor method
		/// @Return: The name of the product that the derived class creates
		virtual std::string className() const = 0;

	private:

		/// Creates an instance of the product that the factory is responsible for
		/// @Return: An instance of this factory's type of product
		virtual AbstractProduct* create() = 0;

#pragma endregion

#pragma region Singleton API

	public:

		/// Finds a factory in the static hashmap, if it exists
		/// @Param className: The name of the factory in question
		/// @Return: A pointer to the factory if it exists, nullptr otherwise
		static Factory<AbstractProduct>* find(const std::string className)
		{
			Factory<AbstractProduct>* result = nullptr;

			auto foundIterator = sFactoryMap.find(className);
			if (foundIterator != sFactoryMap.end())
			{
				result = foundIterator->second;
			}

			return result;
		}

		/// Creates an instance of a product by searching through the hashmap to find the associated key
		/// @Param className: The name of the product being created
		/// @Return: A pointr to the created product if a factory exists to create one. Nullptr otherwise
		static AbstractProduct* create(const std::string className)
		{
			AbstractProduct* result = nullptr;

			auto foundIterator = sFactoryMap.find(className);
			if (foundIterator != sFactoryMap.end())
			{
				result = (*foundIterator).second->create();
			}

			return result;
		}

		/// Accessor to the begin iterator for the static hashmap
		/// @Return: The beginning of the static hashmap of factory pointers
		static typename HashMap<std::string, Factory<AbstractProduct>*>::Iterator begin()
		{
			return sFactoryMap.begin();
		}

		/// Accesssor to the end iterator for the static hashmap
		/// @Return: The end of the static hashmap of factory pointers
		static typename HashMap<std::string, Factory<AbstractProduct>*>::Iterator end()
		{
			return sFactoryMap.end();
		}

	protected:
		
		/// Adds a factory pointer to the static hashmap of factory pointers
		/// @Param factory: The factory pointer being added to the hashmap
		static void add(Factory<AbstractProduct>* const factory)
		{
			if (!sFactoryMap.containsKey(factory->className()))
			{
				sFactoryMap[factory->className()] = factory;
			}
		}

		/// Removes a factory pointer from the static hashmap of factory pointers
		/// @Param factory: The factory pointer being added to the hashmap
		static void remove(const Factory<AbstractProduct>* factory)
		{
			if (sFactoryMap.containsKey(factory->className()))
			{
				sFactoryMap.remove(factory->className());
			}
		}

	private:
		static HashMap<std::string, Factory<AbstractProduct>*> sFactoryMap;

#pragma endregion
	};

	/// The hashmap of string, factory pointer pairs of all factories currently subscribed to the abstract factory
	template <class AbstractProduct>
	HashMap<std::string, Factory<AbstractProduct>*> Factory<AbstractProduct>::sFactoryMap;
}