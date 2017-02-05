#pragma once
namespace Datum
{
	class Datum
	{
	public:
		/// Types of possible Datum
		enum DatumType
		{
			Unknown, // Type not specified
			Integer, // Unsigned integer
			Float,   // Single-precision floating-point value
			Vector,  // 4-vector
			Matrix,  // 4x4 matrix
			Table,   // Pointer to a scope
			String,  // STL string
			Pointer  // Pointer to any RTTI instance
		};

		union Values
		{
			// Should this be populated with DatumTypes? Doesn't seem to work that way
		};

		/// Constructor
		Datum();
		/// Destructor
		~Datum();
		/// Copy constructor
		/// @Param rhs: Datum object being copied
		Datum(const Datum& rhs);
		/// Move copy constructor
		/// @Param rhs: Datum object being copied
		Datum(const Datum&& rhs);
		/// Assignment operator
		/// @Param rhs: Datum object being copied
		/// @Return: A Copy of the specified Datum object
		Datum& operator=(const Datum& rhs);
		/// Move assignment operator
		/// @Param rhs: Datum object being copied
		/// @Return: A Copy of the specified Datum object
		Datum& operator=(const Datum&& rhs);
		/// Comparison operator
		/// @Param rhs: The Datum object being compared against
		/// @Return: True if the two Datum objects are equivalent
		bool operator==(const Datum& rhs);
		/// Negated comparison operator
		/// @Param rhs: The Datum object being compared against
		/// @Return: True if the two Datum objects are not equivalent
		bool operator!=(const Datum& rhs);

		/// The type associated with this object
		/// @Return: The DatumType of this Datum object
		DatumType type() const;
		/// Set the DatumType of the Datum object
		/// @Param type: The new type of the Datum object
		void setType(const DatumType& type);
		/// The number of values in the Datum object
		/// @Return: The number of items associated with this Datum object
		std::uint32_t size() const;
		/// Set number of values and reserve memory if needed
		/// @Param size: the new number of values
		void setSize(std::uint32_t size);
		/// Clear the array without shrinking the capacity
		void clear();
		// TODO: Declare setStorage()
		// TODO: Declare set();
		// TODO: Declare get();
		// TODO: Declare setFromString()
		// TODO: Declare toString();
	};
}