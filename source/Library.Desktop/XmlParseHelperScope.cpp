#include "pch.h"
#include "XmlParseHelperScope.h"
#include "SharedDataScope.h"
#include "Scope.h"
#include <sstream>


namespace Library
{
	XmlParseHelperScope::XmlParseHelperScope():
		mState(State::NotParsing), mMatrixComponentCount(0)
	{
		for (std::uint32_t i = 0; i < 4; i++)
		{
			for (std::uint32_t j = 0; j < 4; j++)
			{
				mMatrixComponents[i][j] = "";
			}
		}
	}

	void XmlParseHelperScope::initialize(XmlParseMaster* const xmlParseMaster)
	{
		mXmlParseMaster = xmlParseMaster;
	}

	bool XmlParseHelperScope::startElementHandler(
		XmlParseMaster::SharedData& sharedData, const std::string& element, 
		const HashMap<std::string, std::string> attributes)
	{
		SharedDataScope* data = sharedData.As<SharedDataScope>();
		if (data == nullptr) { return false; }
		Scope* scope = data->mScope;

		if (element == "Integer")
		{
			mState = State::ParsingInteger;
			Datum& datum = scope->append(element);
			datum.setType(DatumType::Integer);
			datum.setFromString(attributes.find("Value")->second);
		}
		else if (element == "Float")
		{
			mState = State::ParsingFloat;
			Datum& datum = scope->append(element);
			datum.setType(DatumType::Float);
			datum.setFromString(attributes.find("Value")->second);
		}
		else if (element == "Vector")
		{
			mState = (mState == State::ParsingMatrix) ? State::ParsingMatrix : State::ParsingVector;

			std::string x, y, z, w;
			x = attributes.find("X")->second;
			y = attributes.find("Y")->second;
			z = attributes.find("Z")->second;
			w = attributes.find("W")->second;

			if (mState == State::ParsingVector)
			{
				Datum& datum = scope->append(element);
				datum.setType(DatumType::Vector);

				std::stringstream ss;
				ss << "vec4(" << x << "," << y << "," << z << "," << w << ")";
				datum.setFromString(ss.str());
			}
			else if (mState == State::ParsingMatrix)
			{
				mMatrixComponents[mMatrixComponentCount][0] = x;
				mMatrixComponents[mMatrixComponentCount][1] = y;
				mMatrixComponents[mMatrixComponentCount][2] = z;
				mMatrixComponents[mMatrixComponentCount][3] = w;
				
				mMatrixComponentCount++;
				assert(mMatrixComponentCount <= 4);
			}
		}
		else if (element == "Matrix")
		{
			mState = State::ParsingMatrix;
			Datum& datum = scope->append(element);
			datum.setType(DatumType::Matrix);
//			datum.setFromString(attributes.find(element)->second);
			// TODO: Grab all matrix components and build a string from them
		}
		else if (element == "String")
		{
			mState = State::ParsingString;
			Datum& datum = scope->append(element);
			datum.setType(DatumType::String);
			datum.set(attributes.find("Value")->second);
		}
		else if (element == "Scope")
		{
			mState = State::ParsingScope;
			Scope& newScope = scope->appendScope(element);
			data->mScope = &newScope; // Scope becomes the newly appended scope until we're done adding to it
		}

		return false;
	}

	bool XmlParseHelperScope::endElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element)
	{
		SharedDataScope* data = sharedData.As<SharedDataScope>();
		if (data == nullptr) { return false; }
		
		if (element == "Matrix")
		{
			mMatrixComponentCount = 0;
		}

		if (element == "Scope")
		{	// We're done at this level, so jump up one
			assert(data->mScope->getParent() != nullptr);
			data->mScope = data->mScope->getParent();

			if (data->depth() > 0)
			{
				mState = State::ParsingScope;
			}
			else
			{
				mState = State::NotParsing;
			}
		}

		mState = State::NotParsing;
		return false;
	}

	void XmlParseHelperScope::charDataHandler(XmlParseMaster::SharedData& sharedData, const std::string& buffer, const std::uint32_t bufferLength)
	{
		UNREFERENCED_PARAMETER(sharedData);
		UNREFERENCED_PARAMETER(buffer);
		UNREFERENCED_PARAMETER(bufferLength);
		// TODO: Implmeent/remove char data handler
	}
}
