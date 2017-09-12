#include "Datum.h"

namespace Library
{
	/**
	* Template specialization for getting an integer value
	* @Param index: The index of the array being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline std::int32_t& Datum::Get(const std::uint32_t& index)
	{
		if (mType != DatumType::Integer) throw std::exception("Calling Get on invalid Type");
		if (mData.i == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.i[index];
	}

	/**
	* Template specialization for getting an integer value
	* @Param index: The index of the array being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline const std::int32_t& Datum::Get(const std::uint32_t& index) const
	{
		if (mType != DatumType::Integer) throw std::exception("Calling Get on invalid Type");
		if (mData.i == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.i[index];
	}

	/**
	* Template specialization for getting a float value
	* @Param index: The index of the array being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline float& Datum::Get(const std::uint32_t& index)
	{
		if (mType != DatumType::Float) throw std::exception("Calling Get on invalid Type");
		if (mData.f == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.f[index];
	}

	/**
	* Template specialization for getting a float value
	* @Param index: The index of the array being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline const float& Datum::Get(const std::uint32_t& index) const
	{
		if (mType != DatumType::Float) throw std::exception("Calling Get on invalid Type");
		if (mData.f == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.f[index];
	}

	/**
	* Template specialization for getting a vector value
	* @Param index: The index of the array being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline glm::vec4& Datum::Get(const std::uint32_t& index)
	{
		if (mType != DatumType::Vector) throw std::exception("Calling Get on invalid Type");
		if (mData.f == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.v[index];
	}

	/**
	* Template specialization for getting a vector value
	* @Param index: The index of the array being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline const glm::vec4& Datum::Get(const std::uint32_t& index) const
	{
		if (mType != DatumType::Vector) throw std::exception("Calling Get on invalid Type");
		if (mData.f == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.v[index];
	}

	/**
	* Template specialization for getting a matrix value
	* @Param index: The index of the array being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline glm::mat4& Datum::Get(const std::uint32_t& index)
	{
		if (mType != DatumType::Matrix) throw std::exception("Calling Get on invalid Type");
		if (mData.f == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.m[index];
	}

	/**
	* Template specialization for getting a matrix value
	* @Param index: The index of the array being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline const glm::mat4& Datum::Get(const std::uint32_t& index) const
	{
		if (mType != DatumType::Matrix) throw std::exception("Calling Get on invalid Type");
		if (mData.f == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.m[index];
	}

	/**
	* Template specialization for getting a Scope value
	* @Param index: The index of the Scope being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline Scope*& Datum::Get(const std::uint32_t& index)
	{
		if (mType != DatumType::Scope) throw std::exception("Calling et on invalid Type");
		if (mData.sc == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.sc[index];
	}

	/**
	* Template specialization for getting a Scope value
	* @Param index: The index of the Scope being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline Scope* const& Datum::Get(const std::uint32_t& index) const
	{
		if (mType != DatumType::Scope) throw std::exception("Calling et on invalid Type");
		if (mData.sc == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.sc[index];
	}

	/**
	* Template specialization for getting a string value
	* @Param index: The index of the array being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline std::string& Datum::Get(const std::uint32_t& index)
	{
		if (mType != DatumType::String) throw std::exception("Calling Get on invalid Type");
		if (mData.s == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.s[index];
	}

	/**
	* Template specialization for getting a string value
	* @Param index: The index of the array being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline const std::string& Datum::Get(const std::uint32_t& index) const
	{
		if (mType != DatumType::String) throw std::exception("Calling Get on invalid Type");
		if (mData.s == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.s[index];
	}

	/**
	* Template specialization for getting an RTTI pointer value
	* @Param index: The index of the array being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline Library::RTTI*& Datum::Get(const std::uint32_t& index)
	{
		if (mType != DatumType::Pointer) throw std::exception("Calling Get on invalid Type");
		if (mData.r == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.r[index];
	}

	/**
	* Template specialization for getting an RTTI pointer value
	* @Param index: The index of the array being retrieved
	* @Return: The value of the array At the specified index
	* @Exception invalidType: Thrown when calling Get on invalid Type
	* @Exception nullRef: Thrown when attempting call Get on uninitialized data
	* @Exception indexOutOfBounds; Thrown when attempting to access a nonexistent index
	*/
	template<>
	inline Library::RTTI* const& Datum::Get(const std::uint32_t& index) const
	{
		if (mType != DatumType::Pointer) throw std::exception("Calling Get on invalid Type");
		if (mData.r == nullptr) throw std::exception("Attempting to dereference nullptr");
		if (index >= mSize) throw std::exception("Accessing beyond array bounds");
		return mData.r[index];
	}
}