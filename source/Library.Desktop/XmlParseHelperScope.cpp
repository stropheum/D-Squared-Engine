#include "pch.h"
#include "XmlParseHelperScope.h"
#include "SharedDataScope.h"
#include "Scope.h"
#include <sstream>


namespace Library
{
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

	void XmlParseHelperScope::initialize(XmlParseMaster* const xmlParseMaster)
	{
		mXmlParseMaster = xmlParseMaster;
	}

	IXmlParseHelper* XmlParseHelperScope::clone()
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
			Datum& datum = scope->append(attributes.find("Name")->second);
			datum.setType(DatumType::Integer);
			datum.setFromString(attributes.find("Value")->second);
		}
		else if (element == "Float")
		{
			mState = State::ParsingFloat;
			Datum& datum = scope->append(attributes.find("Name")->second);
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
				Datum& datum = scope->append(attributes.find("Name")->second);
				datum.setType(DatumType::Vector);

				std::stringstream ss;
				ss << "vec4(" << x << ", " << y << ", " << z << ", " << w << ")";
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
			mMatrixName = attributes.find("Name")->second;
			// Only use this to set state to start grabbing component vectors
			// TODO: possibly migrate the append call here so we have access to the name we need to create with
		}
		else if (element == "String")
		{
			mState = State::ParsingString;
			Datum& datum = scope->append(attributes.find("Name")->second);
			datum.setType(DatumType::String);
			datum.set(attributes.find("Value")->second);
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
				Scope& newScope = scope->appendScope(attributes.find("Name")->second);
				data->mScope = &newScope; // Scope becomes the newly appended scope until we're done adding to it
			}
		}

		return true;
	}

	bool XmlParseHelperScope::endElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& element)
	{
		SharedDataScope* data = sharedData.As<SharedDataScope>();

		assert(data->depth() > 0);
		if (data == nullptr) { return false; }
		
		if (element == "Integer")
		{
			assert(mState == State::ParsingInteger);
			mState = (data->depth() > 0) ? State::ParsingScope : State::NotParsing;
		}

		else if(element == "Float")
		{
			assert(mState == State::ParsingFloat);
			mState = (data->depth() > 0) ? State::ParsingScope : State::NotParsing;
		}

		else if(element == "Vector")
		{
			assert(mState == State::ParsingVector || mState == State::ParsingMatrix);
			if (data->depth() > 0)
			{
				if (mState != State::ParsingMatrix)
				{
					mState = (data->depth() > 0) ? State::ParsingScope : State::NotParsing;
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

			Datum& datum = data->mScope->append(mMatrixName);
			datum.setType(DatumType::Matrix);
			datum.setFromString(ss.str());

			mMatrixComponentCount = 0;
			assert(mState == State::ParsingMatrix);
			mState = (data->depth() > 0) ? State::ParsingScope : State::NotParsing;
		}

		else if (element == "Scope")
		{	// We're done at this level, so jump up one
			if (data->depth() > 1)
			{
				data->mScope = data->mScope->getParent();
			}

			assert(mState == State::ParsingScope);
			mState = (data->depth() > 0) ? State::ParsingScope : State::NotParsing;
		}

		if (data->depth() == 0) mState = State::NotParsing;
		return true;
	}
}
