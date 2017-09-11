#include "pch.h"
#include "XmlParseHelperScope.h"
#include "SharedDataScope.h"
#include "Scope.h"
#include <sstream>


namespace Library
{
	RTTI_DEFINITIONS(XmlParseHelperScope)

	XmlParseHelperScope::XmlParseHelperScope():
		mState(State::NotParsing), mMatrixName(""), mMatrixComponentCount(0), mScopeHasBeenInitialized(false)
	{
		for (std::uint32_t i = 0; i < 4; i++)
		{
			for (std::uint32_t j = 0; j < 4; j++)
			{
				mMatrixComponents[i][j] = "";
			}
		}
	}

	void XmlParseHelperScope::Initialize(XmlParseMaster* const xmlParseMaster)
	{
		mXmlParseMaster = xmlParseMaster;
	}

	IXmlParseHelper* XmlParseHelperScope::Clone()
	{
		XmlParseHelperScope* clone = new XmlParseHelperScope();

		clone->mState = mState;
		clone->mMatrixComponentCount = mMatrixComponentCount;
		for (std::uint32_t i = 0; i < 4; i++)
		{
			for (std::uint32_t j = 0; j < 4; j++)
			{
				clone->mMatrixComponents[i][j] = mMatrixComponents[i][j];
			}
		}

		return clone;
	}

	bool XmlParseHelperScope::StartElementHandler(
		XmlParseMaster::SharedData& sharedData, const std::string& element, 
		const HashMap<std::string, std::string> attributes)
	{
		SharedDataScope* data = sharedData.As<SharedDataScope>();
		if (data == nullptr) { return false; }
		Scope* scope = data->mScope;

		if (element == "Integer")
		{
			mState = State::ParsingInteger;
			Datum& datum = scope->Append(attributes.Find("Name")->second);
			datum.SetType(DatumType::Integer);
			datum.SetFromString(attributes.Find("Value")->second);
		}
		else if (element == "Float")
		{
			mState = State::ParsingFloat;
			Datum& datum = scope->Append(attributes.Find("Name")->second);
			datum.SetType(DatumType::Float);
			datum.SetFromString(attributes.Find("Value")->second);
		}
		else if (element == "Vector")
		{
			mState = (mState == State::ParsingMatrix) ? State::ParsingMatrix : State::ParsingVector;

			std::string x, y, z, w;
			x = attributes.Find("X")->second;
			y = attributes.Find("Y")->second;
			z = attributes.Find("Z")->second;
			w = attributes.Find("W")->second;

			if (mState == State::ParsingVector)
			{
				Datum& datum = scope->Append(attributes.Find("Name")->second);
				datum.SetType(DatumType::Vector);

				std::stringstream ss;
				ss << "vec4(" << x << ", " << y << ", " << z << ", " << w << ")";
				datum.SetFromString(ss.str());
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
			mMatrixName = attributes.Find("Name")->second;
			// Only use this to Set state to start grabbing component vectors
			// TODO: possibly migrate the Append call here so we have access to the Name we need to Create with
		}
		else if (element == "String")
		{
			mState = State::ParsingString;
			Datum& datum = scope->Append(attributes.Find("Name")->second);
			datum.SetType(DatumType::String);
			datum.Set(attributes.Find("Value")->second);
		}
		else if (element == "Scope")
		{
			mState = State::ParsingScope;

			// TODO: On first scope tag, instantiate new scope
			if (!mScopeHasBeenInitialized)
			{
				data->mScope = new Scope();
				mScopeHasBeenInitialized = true;
			}
			else
			{
				Scope& newScope = scope->AppendScope(attributes.Find("Name")->second);
				data->mScope = &newScope; // Scope becomes the newly appended scope until we're done adding to it
			}
		}

		return true;
	}

	bool XmlParseHelperScope::EndElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element)
	{
		SharedDataScope* data = sharedData.As<SharedDataScope>();

		assert(data->Depth() > 0);
		if (data == nullptr) { return false; }
		
		if (element == "Integer")
		{
			assert(mState == State::ParsingInteger);
			mState = (data->Depth() > 0) ? State::ParsingScope : State::NotParsing;
		}

		else if(element == "Float")
		{
			assert(mState == State::ParsingFloat);
			mState = (data->Depth() > 0) ? State::ParsingScope : State::NotParsing;
		}

		else if(element == "Vector")
		{
			assert(mState == State::ParsingVector || mState == State::ParsingMatrix);
			if (data->Depth() > 0)
			{
				if (mState != State::ParsingMatrix)
				{
					mState = (data->Depth() > 0) ? State::ParsingScope : State::NotParsing;
				}
			}
		}

		else if (element == "Matrix")
		{
			assert(mMatrixComponentCount == 4);
			std::stringstream ss;

			// String format: mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))
			ss << "mat4x4(";
			for (std::uint32_t i = 0; i < 4; i++)
			{
				ss << "(";
				for (std::uint32_t j = 0; j < 4; j++)
				{
					ss << mMatrixComponents[i][j];
					if (j < 3)
					{	// Append commas in the first three elements of the row
						ss << ",";
					}
				}
				ss << ")";
				if (i < 3)
				{	// Append commas in the first three rows of the matrix
					ss << ",";
				}
			}
			ss << ")";

			Datum& datum = data->mScope->Append(mMatrixName);
			datum.SetType(DatumType::Matrix);
			datum.SetFromString(ss.str());

			mMatrixComponentCount = 0;
			assert(mState == State::ParsingMatrix);
			mState = (data->Depth() > 0) ? State::ParsingScope : State::NotParsing;
		}

		else if(element == "String")
		{
			assert(mState == State::ParsingString);
			mState = (data->Depth() > 0) ? State::ParsingScope : State::NotParsing;
		}

		else if (element == "Scope")
		{	// We're done At this level, so jump up one
			if (data->Depth() > 1)
			{
				data->mScope = data->mScope->GetParent();
			}

			assert(mState == State::ParsingScope);
			mState = (data->Depth() > 1) ? State::ParsingScope : State::NotParsing;
		}

		if (data->Depth() == 0) mState = State::NotParsing;
		return true;
	}

	std::string XmlParseHelperScope::ToString() const
	{
		return "Xml Parse Helper Scope";
	}

	bool XmlParseHelperScope::Equals(const RTTI* rhs) const
	{
		if (this == rhs) { return true; }
		if (rhs == nullptr) { return false; }

		XmlParseHelperScope* rhsConverted = rhs->As<XmlParseHelperScope>();
		return (rhsConverted != nullptr) ? operator==(*rhsConverted) : false;
	}

	bool XmlParseHelperScope::operator==(const XmlParseHelperScope& rhs) const
	{
		bool matricesEquivalent = true;
		for (std::uint32_t i = 0; i < 4; i++)
		{
			for (std::uint32_t j = 0; j < 4; j++)
			{
				if (mMatrixComponents[i][j] != rhs.mMatrixComponents[i][j])
				{
					matricesEquivalent = false;
				}
			}
		}

		return	mXmlParseMaster == rhs.mXmlParseMaster &&
			mState == rhs.mState && 
			matricesEquivalent && 
			mScopeHasBeenInitialized == rhs.mScopeHasBeenInitialized;
	}
}
