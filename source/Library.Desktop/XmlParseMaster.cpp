#include "pch.h"
#include "XmlParseMaster.h"
#include "IXmlParseHelper.h"
#include "fstream"


namespace Library
{
	RTTI_DEFINITIONS(XmlParseMaster::SharedData)

	XmlParseMaster::XmlParseMaster(SharedData* const sharedData):
		mActiveFileName(""), mSharedData(sharedData), mDepth(0), mClonedInstance(false)
	{
		mXmlParser = XML_ParserCreate(nullptr);
		XML_SetUserData(mXmlParser, mSharedData);
		XML_SetElementHandler(mXmlParser, startElementHandler, endElementHandler);
		XML_SetCharacterDataHandler(mXmlParser, charDataHandler);
	}

	XmlParseMaster::~XmlParseMaster()
	{
		if (mClonedInstance)
		{
			delete mSharedData;
		}
		
		XML_ParserFree(mXmlParser);
	}

	XmlParseMaster* XmlParseMaster::clone() const
	{
		XmlParseMaster* newParseMaster = new XmlParseMaster(mSharedData->clone());
		newParseMaster->mClonedInstance = true;
		newParseMaster->mActiveFileName = mActiveFileName;
		return newParseMaster;
	}

	void XmlParseMaster::addHelper(IXmlParseHelper& helper)
	{
		mHelpers.pushBack(&helper);
	}

	void XmlParseMaster::removeHelper(IXmlParseHelper& helper)
	{
		mHelpers.remove(&helper);
	}

	void XmlParseMaster::parse(char* const xmlData, const std::uint32_t length, const bool endOfFile) const
	{
		XML_Parse(mXmlParser, xmlData, length, endOfFile);
	}

	void XmlParseMaster::parse(const std::string xmlData, const std::uint32_t length, const bool endOfFile) const
	{
		char* xml = const_cast<char*>(xmlData.c_str());
		XML_Parse(mXmlParser, xml, length, endOfFile);
	}

	void XmlParseMaster::parseFromFile(std::string fileName)
	{
		mActiveFileName = fileName;
		std::ifstream input;
		std::int32_t length;
		input.open(fileName);
		input.seekg(0, std::ios::end);
		length = static_cast<std::int32_t>(input.tellg());
		input.seekg(std::ios::beg);

		char* buffer = new char[length];
		input.read(buffer, length);
		input.close();
		parse(buffer, length, true);
		delete[] buffer;
	}

	const std::string& XmlParseMaster::getFileName() const
	{
		return mActiveFileName;
	}

	void XmlParseMaster::setSharedData(SharedData* const sharedData)
	{
		mSharedData = sharedData;
	}

	XmlParseMaster::SharedData* XmlParseMaster::getSharedData() const
	{
		return mSharedData;
	}

	void XmlParseMaster::startElementHandler(void* userData, const XML_Char* name, const XML_Char** atts)
	{
		SharedData* data = static_cast<SharedData*>(userData);

		HashMap<std::string, std::string> attributes;
		
		for (std::uint32_t i = 0; atts[i]; i += 2)
		{
			std::string key = atts[i];
			std::string value = atts[i + 1];
			attributes.insert(std::pair<std::string, std::string>(key, value));
		}

		Vector<IXmlParseHelper*>& helpers = data->getXmlParaseMaster()->mHelpers;

		for (std::uint32_t i = 0; i < helpers.size(); i++)
		{
			if (helpers[i]->startElementHandler(*data, name, attributes))
			{
				break;
			}
		}

		data->incrementDepth();
	}

	void XmlParseMaster::endElementHandler(void* userData, const XML_Char* name)
	{
		SharedData* data = static_cast<SharedData*>(userData);
		UNREFERENCED_PARAMETER(data);
		UNREFERENCED_PARAMETER(name);
		// TODO: Do something with end element handler
		data->decrementDepth();
	}

	void XmlParseMaster::charDataHandler(void* userData, const XML_Char* s, int len)
	{
		SharedData* data = static_cast<SharedData*>(userData);
		UNREFERENCED_PARAMETER(data);
		UNREFERENCED_PARAMETER(s);
		UNREFERENCED_PARAMETER(len);
		// TODO: Do something with char data handler
	}
}
