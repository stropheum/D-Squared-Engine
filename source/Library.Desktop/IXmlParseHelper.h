#pragma once
#include "HashMap.h"

namespace Library
{
	class XmlParseMaster;
	class IXmlParseHelper
	{
	public:
		explicit IXmlParseHelper(XmlParseMaster& xmlParseMaster);
		virtual ~IXmlParseHelper();
		virtual void initialize() = 0;
		bool startElementHandler(const std::string& element, const HashMap<std::string, std::string> attributes);
		bool endElementHandler(const std::string& element);
		void charDataHandler(const std::string& buffer, const std::uint32_t bufferLength);
		virtual void clone() = 0;
	private:
		XmlParseMaster& mXmlParseMaster;
		const std::string mValidElementName;
	};
}
