#include "pch.h"
#include "Datum.h"

namespace Datum
{
	/// Constructor
	Datum::Datum()
	{
		// TODO: Implement constructor
	}

	/// Destructor
	Datum::~Datum()
	{
		// TODO: Clean up any heap-allocated memory or remove destructor
	}

	/// Copy constructor
	/// @Param rhs: Datum object being copied
	Datum::Datum(const Datum& rhs)
	{
		// TODO: Implement copy constructor
		UNREFERENCED_PARAMETER(rhs);
	}

	/// Move copy constructor
	/// @Param rhs: Datum object being copied
	Datum::Datum(const Datum&& rhs)
	{
		// TODO: Implement move copy constructor
		UNREFERENCED_PARAMETER(rhs);
	}

	/// Assignment operator
	/// @Param rhs: Datum object being copied
	/// @Return: A Copy of the specified Datum object
	Datum& Datum::operator=(const Datum& rhs)
	{
		// TODO: Implement assignment operator
		UNREFERENCED_PARAMETER(rhs);
		return *this;
	}

	/// Move assignment operator
	/// @Param rhs: Datum object being copied
	/// @Return: A Copy of the specified Datum object
	Datum& Datum::operator=(const Datum&& rhs)
	{
		// TODO: Implement move assignment operator
		UNREFERENCED_PARAMETER(rhs);
		return *this;
	}

	/// Comparison operator
	/// @Param rhs: The Datum object being compared against
	/// @Return: True if the two Datum objects are equivalent
	bool Datum::operator==(const Datum& rhs)
	{
		// TODO: Implement comparison operator
		UNREFERENCED_PARAMETER(rhs);
		return true;
	}

	/// Negated comparison operator
	/// @Param rhs: The Datum object being compared against
	/// @Return: True if the two Datum objects are not equivalent
	bool Datum::operator!=(const Datum& rhs)
	{
		return !(operator==(rhs));
	}

	/// The type associated with this object
	/// @Return: The DatumType of this Datum object
	Datum::DatumType Datum::type() const
	{
		// TODO: Implement type method
		return DatumType::Unknown;
	}

	/// Set the DatumType of the Datum object
	/// @Param type: The new type of the Datum object
	void Datum::setType(const DatumType& type)
	{
		// TODO: Implement setType method
		UNREFERENCED_PARAMETER(type);
	}

	/// The number of values in the Datum object
	/// @Return: The number of items associated with this Datum object
	std::uint32_t Datum::size() const
	{
		// TODO: Implement size method
		return 0;
	}

	/// Set number of values and reserve memory if needed
	/// @Param size: the new number of values
	void Datum::setSize(std::uint32_t size)
	{
		// TODO: Implement setSize method
		UNREFERENCED_PARAMETER(size);
	}

	/// Clear the array without shrinking the capacity
	void Datum::clear()
	{
		// TODO: Implement clear method
	}
}
