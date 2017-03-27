#pragma once
#include "HashMap.h"

namespace Library
{
	template <class AbstractProduct> class Factory
	{
#pragma region Abstract base class API

	public:
		Factory() {};
		virtual ~Factory() = default;
		virtual std::string className() const = 0;

	private:
		virtual AbstractProduct* create() = 0;

#pragma endregion

#pragma region Singleton API

	public:
		static Factory<AbstractProduct>* find(const std::string className)
		{
			Factory<AbstractProduct>* result = nullptr;

			auto& foundIterator = sFactoryMap.find(className);
			if (foundIterator != sFactoryMap.end())
			{
				result = *foundIterator;
			}

			return result;
		}

		static AbstractProduct* create(const std::string className)
		{
			AbstractProduct* result = nullptr;

			auto& foundIterator = sFactoryMap.find(className);
			if (foundIterator != sFactoryMap.end())
			{
				result = (*foundIterator).create();
			}

			return result;
		}

	protected:
		static void add(Factory<AbstractProduct>* const factory)
		{
			UNREFERENCED_PARAMETER(factory);
			if (!sFactoryMap.containsKey(factory->className()))
			{
				sFactoryMap[factory->className()] = factory;
			}
		}

		static void remove(const Factory<AbstractProduct>* factory)
		{
			UNREFERENCED_PARAMETER(factory);
			if (sFactoryMap.containsKey(factory->className()))
			{
				sFactoryMap.remove(factory->className());
			}
		}

#pragma endregion

	private:
		static HashMap<std::string, Factory<AbstractProduct>*> sFactoryMap;
	};
}