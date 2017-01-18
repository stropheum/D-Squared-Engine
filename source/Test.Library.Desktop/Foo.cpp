#include "pch.h"
#include "Foo.h"


/**
 * Constructor
 * @Param data: The data being wrapped by the foo object
 */
Foo::Foo(int data)
{
	mData = new int(10);
}

/**
 * Copy constructor
 * @Param rhs: Constant reference to the object being copied
 */
Foo::Foo(const Foo& rhs)
{
	mData = new int(rhs.getData());
}

/**
 * Destructor
 * De-allocates the generic heap allocated int
 */
Foo::~Foo()
{
	delete(mData);
}

/**
 * Assignment operator utilizing deep copy semantics
 */
Foo& Foo::operator=(const Foo& rhs)
{
	mData = new int(rhs.getData());
	return *this;
}

/**
 * Comparison operator which checks all elements for equality
 */
bool Foo::operator==(const Foo& rhs) const
{
	return (this->mData == rhs.mData);
}

/**
 * Accessor method for the int data being wrapped by Foo
 * @Return: the dereferenced int contained by Foo
 */
int Foo::getData() const
{
	return *mData;
}
