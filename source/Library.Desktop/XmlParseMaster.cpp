#include "pch.h"
#include "XmlParseMaster.h"


namespace Library
{
	XmlParseMaster::XmlParseMaster():
		mActiveFileName(""), mSharedData(new SharedData())
	{
		mXmlParser = XML_ParserCreate(nullptr);
		XML_SetUserData(mXmlParser, mSharedData);
		XML_SetElementHandler(mXmlParser, startElementHandler, endElementHandler);
	}

	XmlParseMaster::~XmlParseMaster()
	{
		delete mSharedData;
	}

	XmlParseMaster* XmlParseMaster::clone() const
	{
		XmlParseMaster* newParseMaster = new XmlParseMaster();
		newParseMaster->mActiveFileName = mActiveFileName;
		newParseMaster->mSharedData = mSharedData;
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

	void XmlParseMaster::parse(char* const xmlData, const std::uint32_t length, const bool endOfFile)
	{
		XML_Parse(mXmlParser, xmlData, length, endOfFile);
	}

	void XmlParseMaster::parseFromFile(std::string fileName)
	{
		mActiveFileName = fileName;
		// TODO: Read in file from name and parse it
	}

	const std::string& XmlParseMaster::getFileName() const
	{
		return mActiveFileName;
	}

	void XmlParseMaster::setSharedData(SharedData* const sharedData)
	{
		mSharedData = sharedData;
	}

	XmlParseMaster::SharedData* const XmlParseMaster::getSharedData() const
	{
		return mSharedData;
	}

	void XmlParseMaster::startElementHandler(void *userData, const XML_Char *name, const XML_Char **atts)
	{
		SharedData* data = static_cast<SharedData*>(userData);
		UNREFERENCED_PARAMETER(data);
		UNREFERENCED_PARAMETER(name);
		UNREFERENCED_PARAMETER(atts);
		// TODO: Do something with start element handler
		// TODO: Loop through atts and throw out requests for valid handlers and delegate to them
	}

	void XmlParseMaster::endElementHandler(void* userData, const XML_Char* name)
	{
		SharedData* data = static_cast<SharedData*>(userData);
		UNREFERENCED_PARAMETER(data);
		UNREFERENCED_PARAMETER(name);
		// TODO: Do something with end element handler
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
