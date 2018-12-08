#pragma once
#include "XmlParseMaster.h"
#include "RTTI.h"
#include "WorldState.h"


namespace Library
{
    class SharedDataScope : public XmlParseMaster::SharedData
    {
        RTTI_DECLARATIONS(SharedDataScope, XmlParseMaster::SharedData)

    public:

#pragma region Construction/Copy/Assignment

        SharedDataScope();

        ~SharedDataScope();

        SharedDataScope(const SharedDataScope& rhs) = delete;

        SharedDataScope& operator=(const SharedDataScope& rhs) = delete;

        SharedDataScope(SharedDataScope&& rhs) = delete;

        SharedDataScope& operator=(SharedDataScope&& rhs) = delete;

#pragma endregion

        /**
         * Clones a copy of the current SharedData object and returns a newly allocated one
         * @Return: A freshly heap-allocated SharedData instance with the same state as this
         */
        SharedData* Clone() override;

        /**
         * RTTI ToString representation of the shared data class
         * @Return: A string representation of the class Name
         */
        std::string ToString() const override;

        /**
         * RTTI Equals comparison
         * @Param rhs: The RTTI object being compared against
         * @Return: True if the objects are shared data and identical pointers
         */
        bool Equals(const RTTI* rhs) const override;

        Scope* mScope; // The scope data of this object
        WorldState mWorldState;

    };
}