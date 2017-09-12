#pragma once
#include "IXmlParseHelper.h"
#include "RTTI.h"


namespace Library
{
	class XmlParseHelperScope :
		public IXmlParseHelper
	{
		RTTI_DECLARATIONS(XmlParseHelperScope, IXmlParseHelper)

	public:
		
#pragma region Construction/Copy/Assignment

		XmlParseHelperScope();

		~XmlParseHelperScope() = default;

		XmlParseHelperScope(const XmlParseHelperScope& rhs) = delete;

		XmlParseHelperScope& operator=(const XmlParseHelperScope& rhs) = delete;

		XmlParseHelperScope(XmlParseHelperScope&& rhs) = delete;

		XmlParseHelperScope& operator=(XmlParseHelperScope&& rhs) = delete;

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
		 * Comparison operator
		 * @Param rhs: The XmlParseHelperScope being compared against
		 * @Return: True if the two parse helpers are equivalent
		 */
		bool operator==(const XmlParseHelperScope& rhs) const;

	private:
		enum State
		{
			NotParsing,
			ParsingInteger,
			ParsingFloat,
			ParsingVector,
			ParsingMatrix,
			ParsingString,
			ParsingScope,
		};
		State mState;
		std::string mMatrixName;
		std::uint32_t mMatrixComponentCount;
		std::string mMatrixComponents[4][4];
		bool mScopeHasBeenInitialized;
	};
}