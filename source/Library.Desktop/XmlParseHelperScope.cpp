#include "pch.h"
#include "XmlParseHelperScope.h"
#include "SharedDataScope.h"
#include "Scope.h"
#include <sstream>


namespace Library
{
	XmlParseHelperScope::XmlParseHelperScope():
		mState(State::NotParsing)
	{
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
			Datum& datum = scope->append(element);
			datum.setType(DatumType::Vector);
			
			std::string x, y, z, w;
			x = attributes.find("X")->second;
			y = attributes.find("Y")->second;
			z = attributes.find("Z")->second;
			w = attributes.find("W")->second;
			
			std::stringstream ss;
			ss << "vec4(" << x << "," << y << "," << z << "," << w << ")";
			datum.setFromString(ss.str());
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
			// TODO: Track scope depth and when ending scope, check if depth is greater than zero, set state back to parsing scope
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
		
		if (element == "Scope")
		{	// We're done at this level, so jump up one
			assert(data->mScope->getParent() != nullptr);
			data->mScope = data->mScope->getParent();
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
