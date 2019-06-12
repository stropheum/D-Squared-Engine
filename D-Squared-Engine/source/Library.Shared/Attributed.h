#pragma once
#include "Scope.h"


namespace Library
{
    class Attributed : public Scope
    {
        RTTI_DECLARATIONS(Attributed, Scope)

    public:

#pragma region Construction/Copy/Assignment

        Attributed();

        virtual ~Attributed();

        Attributed(const Attributed& rhs);

        Attributed& operator=(const Attributed& rhs);

        Attributed(Attributed&& rhs) noexcept;

        Attributed& operator=(Attributed&& rhs) noexcept;

#pragma endregion

        /**
         *  Populates the attributes
         */
        void Populate();

        /**
         * Determines if the specified string is a prescribed attribute
         * @Param Name: The attribute being checked
         * @Return: True if the attribute is a prescribed attribute
         */
        bool IsPrescribedAttribute(const std::string& name) const;

        /**
         * Determines if the specified string is an auxiliary attribute
         * @Param Name: The attribute being checked
         * @Return: True if the attribute is an auxiliary attribute
         */
        bool IsAuxiliaryAttribute(const std::string& name) const;

        /**
         * Determines if the specified string is an attribute
         * @Param Name: The attribute being checked
         * @Return: True if the attribute is an attribute
         */
        bool IsAttribute(const std::string& name) const;

        /**
         * Adds an auxiliary attribute to the current collection
         * @Param Name: The Name of the new auxiliary attribute
         * @Return: A reference to the Datum created from the appended attribute
         */
        Datum& AppendAuxiliaryAttribute(const std::string& name);

    protected:

        class Signature;

        // This vector is used for populating prescribed attributes in children of attributed
        Vector<Signature> m_prescribedAttributes;

    };
}