#pragma once
class Foo
{
public:
	/**
	 * Default constructor
	 */
	Foo();

	/**
	* Constructor
	* @Param data: The data being wrapped by the foo object
	*/
	explicit Foo(int data);
	
	/**
	* Copy constructor
	* @Param rhs: Constant reference to the object being copied
	*/
	Foo(const Foo& rhs);

	/**
	* Destructor
	* De-allocates the generic heap allocated int
	*/
	~Foo();

	/**
	* Assignment operator utilizing deep copy semantics
	*/
	Foo& operator=(const Foo& rhs);

	/**
	* Comparison operator which checks all elements for equality
	*/
	bool operator==(const Foo& rhs) const;

	/**
	 * Comparison operator which returns the negation of operator==
	 */
	bool operator!=(const Foo& rhs) const;

	/**
	* Accessor method for the int data being wrapped by Foo
	* @Return: the dereferenced int contained by Foo
	*/
	int getData() const;

private:
	/// Member int that is wrapped by foo
	int* mData;
};

