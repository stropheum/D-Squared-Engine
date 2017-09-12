#pragma once
#include "HashMap.h"

namespace Library
{
	template <class AbstractProduct> class Factory
	{
#pragma region Abstract base class API

#pragma region ConcreteFactory Macro

/**
 * Macro used to generate factories for concrete products. 
 * This macro should be put in the header file of any class 
 * that wishes to have an associated factory
 */
#define ConcreteFactory(AbstractProduct, ConcreteProduct)				\
	class ConcreteProduct##Factory : public Factory<AbstractProduct>	\
	{																	\
	public:																\
		ConcreteProduct##Factory() { Add(this); }						\
		~ConcreteProduct##Factory() { Remove(this); }					\
																		\
		virtual std::string ClassName() const override					\
		{																\
			return #ConcreteProduct;									\
		}																\
																		\
		virtual AbstractProduct* Create() override						\
		{																\
			AbstractProduct* product = new ConcreteProduct();			\
			assert(product != nullptr);									\
			return product;												\
		}																\
	};																	\

#pragma endregion

	public:

#pragma region Construction/Copy/Assignment

		Factory() {};

		virtual ~Factory() = default;

		Factory(const Factory& rhs) = delete;

		Factory& operator=(const Factory& rhs) = delete;

		Factory(Factory&& rhs) = delete;

		Factory& operator=(Factory&& rhs) = delete;

#pragma endregion

		/**
		 * Class Name accessor method
		 * @Return: The Name of the product that the derived class creates
		 */
		virtual std::string ClassName() const = 0;

	private:

		/**
		 * Creates an instance of the product that the factory is responsible for
		 * @Return: An instance of this factory's Type of product
		 */
		virtual AbstractProduct* Create() = 0;

#pragma endregion

#pragma region Singleton API

	public:

		/**
		 * Finds a factory in the static hashmap, if it exists
		 * @Param ClassName: The Name of the factory in question
		 * @Return: A pointer to the factory if it exists, nullptr otherwise
		 */
		static Factory<AbstractProduct>* Find(const std::string& className)
		{
			Factory<AbstractProduct>* result = nullptr;

			auto foundIterator = sFactoryMap.Find(className);
			if (foundIterator != sFactoryMap.end())
			{
				result = foundIterator->second;
			}

			return result;
		}

		/**
		 * Creates an instance of a product by searching through the hashmap to Find the associated key
		 * @Param ClassName: The Name of the product being created
		 * @Return: A pointr to the created product if a factory exists to Create one. Nullptr otherwise
		 */
		static AbstractProduct* Create(const std::string& className)
		{
			AbstractProduct* result = nullptr;

			auto foundIterator = sFactoryMap.Find(className);
			if (foundIterator != sFactoryMap.end())
			{
				result = (*foundIterator).second->Create();
			}

			return result;
		}

		/**
		 * Accessor to the begin iterator for the static hashmap
		 * @Return: The beginning of the static hashmap of factory pointers
		 */
		static typename HashMap<std::string, Factory<AbstractProduct>*>::Iterator Begin()
		{
			return sFactoryMap.begin();
		}

		/**
		 * Accesssor to the end iterator for the static hashmap
		 * @Return: The end of the static hashmap of factory pointers
		 */
		static typename HashMap<std::string, Factory<AbstractProduct>*>::Iterator End()
		{
			return sFactoryMap.end();
		}

	protected:
		
		/**
		 * Adds a factory pointer to the static hashmap of factory pointers
		 * @Param factory: The factory pointer being added to the hashmap
		 */
		static void Add(Factory<AbstractProduct>* const factory)
		{
			if (!sFactoryMap.ContainsKey(factory->ClassName()))
			{
				sFactoryMap[factory->ClassName()] = factory;
			}
		}

		/**
		 * Removes a factory pointer from the static hashmap of factory pointers
		 * @Param factory: The factory pointer being added to the hashmap
		 */
		static void Remove(const Factory<AbstractProduct>* factory)
		{
			if (sFactoryMap.ContainsKey(factory->ClassName()))
			{
				sFactoryMap.Remove(factory->ClassName());
			}
		}

	private:

		// The hashmap of string, factory pointer pairs of all factories currently subscribed to the abstract factory
		static HashMap<std::string, Factory<AbstractProduct>*> sFactoryMap;

#pragma endregion
	};

	template <class AbstractProduct>
	HashMap<std::string, Factory<AbstractProduct>*> Factory<AbstractProduct>::sFactoryMap;
}