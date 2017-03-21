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
		explicit IXmlParseHelper(XmlParseMaster* const xmlParseMaster=nullptr);
		virtual ~IXmlParseHelper();
		virtual void initialize(XmlParseMaster* const xmlParseMaster) = 0;
		virtual bool startElementHandler(XmlParseMaster::SharedData& sharedData,  const std::string& element, const HashMap<std::string, std::string> attributes);
		virtual bool endElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element);
		virtual void charDataHandler(XmlParseMaster::SharedData& sharedData, const std::string& buffer, const std::uint32_t bufferLength);
		virtual IXmlParseHelper* clone() = 0;

		std::string ToString() const override;
		bool Equals(const RTTI* rhs) const override;
	protected:
		XmlParseMaster* mXmlParseMaster;
		const std::string mValidElementName;
	};
}
