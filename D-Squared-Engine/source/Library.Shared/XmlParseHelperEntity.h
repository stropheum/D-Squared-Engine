#pragma once
#include "XmlParseMaster.h"
#include "HashMap.h"
#include "IXmlParseHelper.h"


namespace Library
{
    class XmlParseHelperEntity : public IXmlParseHelper
    {
        RTTI_DECLARATIONS(XmlParseHelperEntity, IXmlParseHelper)

    public:

#pragma region Construction/Copy/Assignment

        XmlParseHelperEntity();

        ~XmlParseHelperEntity() = default;

        XmlParseHelperEntity(const XmlParseHelperEntity& rhs) = delete;

        XmlParseHelperEntity& operator=(const XmlParseHelperEntity& rhs) = delete;

        XmlParseHelperEntity(XmlParseHelperEntity&& rhs) = delete;

        XmlParseHelperEntity& operator=(XmlParseHelperEntity&& rhs) = delete;

#pragma endregion

        /**
         * Initializes the helper to be associated with a Parse master
         * @Param xmlParseMaster: The Parse master that will be associated with this helper
         */
        void Initialize(XmlParseMaster* const xmlParseMaster) override;

        /**
         * Method used for copying instances of Parse helpers
         * @Return: Pointer to the freshly allocated Parse helper
         */
        IXmlParseHelper* Clone() override;

        /**
         * Handles elements from the Expat callback with the same Name
         * @Param sharedData: The shared data object being written to
         * @Param element: The Name of the entry being parsed
         * @Param attributes: The collection of string,string pairs of attributes associated with the entry
         * @Return: True if the helper can handle parsing the data
         */
        bool StartElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element, const HashMap<std::string, std::string> attributes) override;

        /**
         * Handles elements from the Expat callback with the same Name
         * @Param sharedData: The shared data object being written to
         * @Param element: The Name of the entry being parsed
         * @Return: True if the helper can handle parsing the data
         */
        bool EndElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element) override;

        /**
         * RTTI method for having a string representation of the Parse helper
         */
        std::string ToString() const override;

        /**
         * RTTI method for comparing one Parse helper to the other
         */
        bool Equals(const RTTI* rhs) const override;

        /**
         * Comparison operator
         * @Param rhs: The Parse helper beign compared against
         * @Return: true if the Parse helpers are equivalent
         */
        bool operator==(const XmlParseHelperEntity& rhs) const;

    private:

        enum State
        {
            NotParsing,
            ParsingInteger,
            ParsingFloat,
            ParsingVector,
            ParsingMatrix,
            ParsingString,
            ParsingWorld,
            ParsingSector,
            ParsingEntity,
            ParsingAction
        };

        enum ActionType
        {
            GenericAction,
            IfAction,
            CreateAction,
            DestroyAction
        };

        State m_state;
        State m_previousState;
        ActionType m_actionSubType;
        std::string m_matrixName;
        std::uint32_t m_matrixComponentCount;
        std::string m_matrixComponents[4][4];
        bool m_scopeHasBeenInitialized;

    };
}