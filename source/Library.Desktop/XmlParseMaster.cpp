#include "pch.h"
#include "XmlParseMaster.h"
#include "expat.h"


namespace Library
{
	XmlParseMaster::XmlParseMaster():
		mActiveFileName(""), mSharedData(nullptr)
	{
		// TODO: Implement constructor
	}

	XmlParseMaster::~XmlParseMaster()
	{
		delete mSharedData;
	}

	XmlParseMaster* XmlParseMaster::clone()
	{
		// TODO: Implement clone method
		return this;
	}

	void XmlParseMaster::addHelper(const IXmlParseHelper& helper)
	{
		UNREFERENCED_PARAMETER(helper);
		// TODO: Implement method
	}

	void XmlParseMaster::removeHelper(const IXmlParseHelper& helper)
	{
		UNREFERENCED_PARAMETER(helper);
		// TODO: Implement method
	}

	void XmlParseMaster::parse(char** xmlData, std::uint32_t length, bool endOfFile)
	{
		UNREFERENCED_PARAMETER(xmlData);
		UNREFERENCED_PARAMETER(length);
		UNREFERENCED_PARAMETER(endOfFile);
		// TODO: Thinly wrap expat's "parse" function
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
