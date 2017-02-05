#pragma once
#include <cstdint>
#include "../Test.Library.Desktop/Foo.h"

namespace HashMap
{
	template <class T> class DefaultHash
	{
	public:
		std::uint32_t operator()(const T& key) const
		{
			const std::int8_t* bytes = reinterpret_cast<const std::int8_t*>(&key);

			std::uint32_t hash = 0;
			std::uint32_t size = strlen(reinterpret_cast<const char*>(bytes));
			for (std::uint32_t i = 0; i < size; i++)
			{
				hash += bytes[i];
			}

			return hash;
		}
	};

	template <> 
	class DefaultHash<int>
	{
	public:
		std::uint32_t operator()(const int& key) const
		{
			const std::int8_t* bytes = reinterpret_cast<const std::int8_t*>(&key);

			std::uint32_t hash = 0;
			auto size = strlen(reinterpret_cast<const char*>(bytes));
			for (std::uint32_t i = 0; i < size; i++)
			{
				hash += bytes[i];
			}
			
			return hash;
		}
	};

	template<>
	class DefaultHash<std::string>
	{
	public:
		std::uint32_t operator()(const std::string& key) const
		{
			std::uint32_t hash = 0;

			for (std::uint32_t i = 0; i < key.length(); i++)
			{
				hash += key.at(i);
			}

			return hash;
		}
	};

	template<>
	class DefaultHash<char*>
	{
	public:
		std::uint32_t operator()(const char* key) const
		{
			std::uint32_t hash = 0;

			for (std::uint32_t i = 0; i < strlen(key); i++)
			{
				hash += key[i];
			}

			return hash;
		}
	};

	template<>
	class DefaultHash<int*>
	{
	public:
		std::uint32_t operator()(const int* key) const
		{
			const std::int8_t* bytes = reinterpret_cast<const std::int8_t*>(key);

			std::uint32_t hash = 0;
			for (std::uint32_t i = 0; i < strlen(reinterpret_cast<const char*>(bytes)); i++)
			{
				hash += bytes[i];
			}

			return hash;
		}
	};

	template<>
	class DefaultHash<Foo>
	{
	public:
		std::uint32_t operator()(const Foo& key) const
		{
			std::uint32_t value = key.getData();
			const std::int8_t* bytes = reinterpret_cast<const std::int8_t*>(&value);

			std::uint32_t hash = 0;
			auto size = strlen(reinterpret_cast<const char*>(bytes));
			for (std::uint32_t i = 0; i < size; i++)
			{
				hash += bytes[i];
			}

			return hash;
		}
	};
}
