#pragma once
#include "IXmlParseHelper.h"

namespace Library
{
	class XmlParseHelperScope :
		public IXmlParseHelper
	{
	public:
		/// Constructor for xml parse helper scope
		XmlParseHelperScope();

		/// Initializes the helper to be associated with a parse master
		/// @Param xmlParseMaster: The parse master that will be associated with this helper
		void initialize(XmlParseMaster* const xmlParseMaster) override;

		/// Handles elements from the Expat callback with the same name
		/// @Param sharedData: The shared data object being written to
		/// @Param element: The name of the entry being parsed
		/// @Param attributes: The collection of string,string pairs of attributes associated with the entry
		/// @Return: True if the helper can handle parsing the data
		bool startElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element, const HashMap<std::string, std::string> attributes) override;

		/// Handles elements from the Expat callback with the same name
		/// @Param sharedData: The shared data object being written to
		/// @Param element: The name of the entry being parsed
		/// @Return: True if the helper can handle parsing the data
		bool endElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element) override;

		/// Handles elements from the Expat callback with the same name
		/// @Param sharedData: The shared data object being written to
		/// @Param buffer: The character data being parsed
		/// @Param bufferLength: The number of characters in the buffer
		/// @Return: True if the helper can handle parsing the data
		void charDataHandler(XmlParseMaster::SharedData& sharedData, const std::string& buffer, const std::uint32_t bufferLength) override;

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
		std::uint32_t mMatrixComponentCount;
		std::string mMatrixComponents[4][4];
	};
}