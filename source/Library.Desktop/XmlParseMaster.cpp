#include "pch.h"
#include "XmlParseMaster.h"
#include "expat.h"


namespace Library
{
	XmlParseMaster::XmlParseMaster():
		mActiveFileName(""), mSharedData(nullptr)
	{}

	XmlParseMaster::~XmlParseMaster()
	{
		delete mSharedData;
	}

	XmlParseMaster* XmlParseMaster::clone()
	{
		// TODO: Implement clone method
		return this;
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
		// What do I pass in as the XML_Parser argument?
		XML_Parse(nullptr, xmlData, length, endOfFile);
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

	void XmlParseMaster::startElementHandler()
	{
		// TODO: Implement method
	}

	void XmlParseMaster::endElementHandler()
	{
		// TODO: Implement method
	}

	void XmlParseMaster::charDataHandler()
	{
		// TODO: Implement method
	}
}
