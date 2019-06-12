#include "pch.h"
#include "Foo.h"

/**
 * Default constructor
 */
Foo::Foo() :m_data(new int(1)) {}

/**
 * Constructor
 * @Param data: The data being wrapped by the foo object
 */
Foo::Foo(int data) :
    m_data(new int(data)) {}

/**
 * Copy constructor
 * @Param rhs: Constant reference to the object being copied
 */
Foo::Foo(const Foo& rhs) :
    Foo(*(rhs.m_data)) {}

/**
 * Destructor
 * De-allocates the generic heap allocated int
 */
Foo::~Foo()
{
    delete(m_data);
}

/**
 * Assignment operator utilizing deep copy semantics
 */
Foo& Foo::operator=(const Foo& rhs)
{
    *m_data = *rhs.m_data;
    return *this;
}

/**
 * Comparison operator which checks all elements for equality
 */
bool Foo::operator==(const Foo& rhs) const
{
    return (this->getData() == rhs.getData());
}

/**
 * Comparison operator which returns the negation of operator==
 */
bool Foo::operator!=(const Foo& rhs) const
{
    return !(operator==(rhs));
}

/**
 * Accessor method for the int data being wrapped by Foo
 * @Return: the dereferenced int contained by Foo
 */
int Foo::getData() const
{
    return *m_data;
}