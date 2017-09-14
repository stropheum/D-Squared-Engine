#pragma once
#include <cstdint>

namespace Library
{
	template <class T> class DefaultHash
	{
	public:
		std::uint32_t operator()(const T& key) const
		{
			const std::int8_t* bytes = reinterpret_cast<const std::int8_t*>(&key);

			std::uint32_t hash = 0;
			std::uint32_t size = sizeof(T);
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
			return key; // Integers are in and of themselves unique integers, no need to hash
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
	class DefaultHash<const std::string>
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

	/// Partial pointer specialization
	template<typename T>
	class DefaultHash<T*>
	{
	public:
		std::uint32_t operator()(const T* key) const
		{
			const std::int8_t* bytes = reinterpret_cast<const std::int8_t*>(key);

			std::uint32_t hash = 0;
			std::uint32_t size = sizeof(T*);
			for (std::uint32_t i = 0; i < size; i++)
			{
				hash += bytes[i];
			}

			return hash;
		}
	};
}
