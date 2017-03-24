#pragma once
#include "HashMap.h"
#include "XmlParseMaster.h"
#include "RTTI.h"

namespace Library
{
	class IXmlParseHelper :
		public RTTI
	{
		RTTI_DECLARATIONS(IXmlParseHelper, RTTI)
	public:
		/// Constructor
		/// @Param xmlParseMaster: The parse master associated with this helper
		explicit IXmlParseHelper(XmlParseMaster* const xmlParseMaster=nullptr);

		/// Destructor
		virtual ~IXmlParseHelper();

		/// Initializes the helper to be associated with a parse master
		/// @Param xmlParseMaster: The parse master that will be associated with this helper
		virtual void initialize(XmlParseMaster* const xmlParseMaster) = 0;

		/// Handles elements from the Expat callback with the same name
		/// @Param sharedData: The shared data object being written to
		/// @Param element: The name of the entry being parsed
		/// @Param attributes: The collection of string,string pairs of attributes associated with the entry
		/// @Return: True if the helper can handle parsing the data
		virtual bool startElementHandler(XmlParseMaster::SharedData& sharedData,  const std::string& element, const HashMap<std::string, std::string> attributes) = 0;

		/// Handles elements from the Expat callback with the same name
		/// @Param sharedData: The shared data object being written to
		/// @Param element: The name of the entry being parsed
		/// @Return: True if the helper can handle parsing the data
		virtual bool endElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element) = 0;

		/// Handles elements from the Expat callback with the same name
		/// @Param sharedData: The shared data object being written to
		/// @Param buffer: The character data being parsed
		/// @Param bufferLength: The number of characters in the buffer
		/// @Return: True if the helper can handle parsing the data
		virtual void charDataHandler(XmlParseMaster::SharedData& sharedData, const std::string& buffer, const std::uint32_t bufferLength);

		/// Method used for copying instances of parse helpers
		/// @Return: Pointer to the freshly allocated parse helper
		virtual IXmlParseHelper* clone() = 0;

		/// RTTI ToString representation of the parse helper
		/// @Return: A string representation of the class name
		std::string ToString() const override;

		/// RTTI Equals comparison
		/// @Param rhs: The RTTI object being compared against
		/// @Return: True if the objects are shared data and identical pointers
		bool Equals(const RTTI* rhs) const override;
	protected:
		XmlParseMaster* mXmlParseMaster;
		const std::string mValidElementName;
	};
}
