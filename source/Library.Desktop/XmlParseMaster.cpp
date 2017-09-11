#include "pch.h"
#include "XmlParseMaster.h"
#include "fstream"


using namespace std;

namespace Library
{
	RTTI_DEFINITIONS(XmlParseMaster::SharedData)

	XmlParseMaster::XmlParseMaster(SharedData* const sharedData):
		mXmlParser(XML_ParserCreate(nullptr)), mActiveFileName(""), mSharedData(sharedData), mDepth(0), mClonedInstance(false), mHelpersAreInitialized(false)
	{
		XML_SetUserData(mXmlParser, mSharedData);
		XML_SetElementHandler(mXmlParser, StartElementHandler, EndElementHandler);
		XML_SetCharacterDataHandler(mXmlParser, CharDataHandler);
	}

	XmlParseMaster::~XmlParseMaster()
	{
		if (mClonedInstance)
		{
			delete mSharedData;

			for (uint32_t i = 0; i < mHelpers.Size(); i++)
			{
				delete mHelpers[i];
			}
			mHelpers.Clear();
		}
		
		XML_ParserFree(mXmlParser);
	}

	XmlParseMaster* XmlParseMaster::Clone() const
	{
		XmlParseMaster* newParseMaster = new XmlParseMaster(mSharedData->Clone());
		newParseMaster->mClonedInstance = true;
		newParseMaster->mActiveFileName = mActiveFileName;
		
		for (uint32_t i = 0; i < mHelpers.Size(); i++)
		{
			newParseMaster->mHelpers.PushBack(mHelpers[i]->Clone());
		}

		return newParseMaster;
	}

	void XmlParseMaster::AddHelper(IXmlParseHelper& helper)
	{
		mHelpers.PushBack(&helper);
	}

	void XmlParseMaster::RemoveHelper(IXmlParseHelper& helper)
	{
		mHelpers.Remove(&helper);
	}

	void XmlParseMaster::Parse(char* const xmlData, const uint32_t& length, const bool endOfFile)
	{
		HandleHelperInitialization();
		XML_Parse(mXmlParser, xmlData, length, endOfFile);
	}

	void XmlParseMaster::ParseFromFile(const string& fileName)
	{
		HandleHelperInitialization();

		mActiveFileName = fileName;
		ifstream input;
		input.open(fileName, ios::binary);
		input.seekg(0, ios::end);
		int32_t length = static_cast<int32_t>(input.tellg());
		input.seekg(ios::beg);

		char* buffer = new char[length];
		input.read(buffer, length);
		input.close();
		Parse(buffer, length, true);
		delete[] buffer;
	}

	const string& XmlParseMaster::GetFileName() const
	{
		return mActiveFileName;
	}

	void XmlParseMaster::SetSharedData(SharedData* const sharedData)
	{
		mSharedData = sharedData;
	}

	XmlParseMaster::SharedData* XmlParseMaster::GetSharedData() const
	{
		return mSharedData;
	}

	void XmlParseMaster::StartElementHandler(void* userData, const XML_Char* name, const XML_Char** atts)
	{
		SharedData* data = static_cast<SharedData*>(userData);

		HashMap<string, string> attributes;
		
		for (uint32_t i = 0; atts[i]; i += 2)
		{
			string key = atts[i];
			string value = atts[i + 1];
			attributes[key] = value;
		}

		Vector<IXmlParseHelper*>& helpers = data->GetXmlParseMaster()->mHelpers;

		for (uint32_t i = 0; i < helpers.Size(); i++)
		{
			if (helpers[i]->StartElementHandler(*data, name, attributes))
			{
				break;
			}
		}

		data->IncrementDepth();
	}

	void XmlParseMaster::EndElementHandler(void* userData, const XML_Char* name)
	{
		SharedData* data = static_cast<SharedData*>(userData);
		Vector<IXmlParseHelper*>& helpers = data->GetXmlParseMaster()->mHelpers;

		for (uint32_t i = 0; i < helpers.Size(); i++)
		{
			if (helpers[i]->EndElementHandler(*data, name))
			{
				break;
			}
		}

		data->DecrementDepth();
	}

	void XmlParseMaster::CharDataHandler(void* userData, const XML_Char* s, int len)
	{
		SharedData* data = static_cast<SharedData*>(userData);
		UNREFERENCED_PARAMETER(data);
		UNREFERENCED_PARAMETER(s);
		UNREFERENCED_PARAMETER(len);
	}

	void XmlParseMaster::HandleHelperInitialization()
	{
		if (!mHelpersAreInitialized)
		{
			for (uint32_t i = 0; i < mHelpers.Size(); i++)
			{	// Initialize all Parse helpers so they reflect the correct Parse master
				mHelpers[i]->Initialize(this);
			}
			mHelpersAreInitialized = true;
		}
	}
}
