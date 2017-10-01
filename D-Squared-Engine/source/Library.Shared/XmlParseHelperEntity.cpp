#include "pch.h"
#include "XmlParseHelperEntity.h"


using namespace std;

namespace Library
{
	RTTI_DEFINITIONS(XmlParseHelperEntity)

		XmlParseHelperEntity::XmlParseHelperEntity() :
		mState(State::NotParsing), mPreviousState(State::NotParsing), mActionSubType(), mMatrixName(""), mMatrixComponentCount(0), mScopeHasBeenInitialized(false)
	{
		for (uint32_t i = 0; i < 4; i++)
		{
			for (uint32_t j = 0; j < 4; j++)
			{
				mMatrixComponents[i][j] = "";
			}
		}
	}

	void XmlParseHelperEntity::Initialize(XmlParseMaster* const xmlParseMaster)
	{
		mXmlParseMaster = xmlParseMaster;
	}

	IXmlParseHelper* XmlParseHelperEntity::Clone()
	{
		XmlParseHelperEntity* clone = new XmlParseHelperEntity();

		clone->mState = mState;
		clone->mMatrixComponentCount = mMatrixComponentCount;
		for (uint32_t i = 0; i < 4; i++)
		{
			for (uint32_t j = 0; j < 4; j++)
			{
				clone->mMatrixComponents[i][j] = mMatrixComponents[i][j];
			}
		}

		return clone;
	}

	bool XmlParseHelperEntity::StartElementHandler(
		XmlParseMaster::SharedData& sharedData, const string& element,
		const HashMap<string, string> attributes)
	{
		// Store off state to revert once the end element handler has been met
		mPreviousState = (
            mState == State::NotParsing || 
            mState == State::ParsingWorld || 
            mState == State::ParsingSector || 
            mState == State::ParsingEntity) 
			? mState 
			: mPreviousState; 

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

			string x = attributes.Find("X")->second;
			string y = attributes.Find("Y")->second;
			string z = attributes.Find("Z")->second;
			string w = attributes.Find("W")->second;

			if (mState == State::ParsingVector)
			{
				assert(attributes.Find("Name") != attributes.end());
				pair<string, string> pair = *attributes.Find("Name");
				Datum& datum = scope->Append(attributes.Find("Name")->second);
				datum.SetType(DatumType::Vector);

				stringstream ss;
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
		}

		else if (element == "String")
		{
			mState = State::ParsingString;
			Datum& datum = scope->Append(attributes.Find("Name")->second);
			datum.SetType(DatumType::String);
			datum.Set(attributes.Find("Value")->second);
		}

		else if (element == "World")
		{
			if (mState != State::NotParsing || mScopeHasBeenInitialized)
			{
				throw exception("Already parsing while attempting to parse a mWorld");
			}

			mState = State::ParsingWorld;
			data->mScope = new World();
			data->mScope->As<World>()->SetName(attributes.Find("Name")->second);
			mScopeHasBeenInitialized = true;
		}

		else if(element == "Sector" || !mScopeHasBeenInitialized)
		{
			assert(data->mScope->Is(World::TypeIdClass()));
			if (mState != State::ParsingWorld)
			{
				throw exception("Attempting to parse a mSector when not in a mWorld");
			}

			mState = State::ParsingSector;

			World* world = data->mScope->As<World>();
			Sector* sector = world->CreateSector(attributes.Find("Name")->second);
			data->mScope = sector;
		}

		else if (element == "Entity" || !mScopeHasBeenInitialized)
		{
			assert(data->mScope->Is(Sector::TypeIdClass()));
			if(mState != State::ParsingSector)
			{
				throw exception("Attempting to parse an mEntity when not in a mSector");
			}

			mState = State::ParsingEntity;
			string className = attributes.Find("ClassName")->second;
			string instanceName = attributes.Find("InstanceName")->second;

			Sector* sector = data->mScope->As<Sector>();
			Entity* entity = sector->CreateEntity(className, instanceName);

			data->mScope = entity;
		}

		else if (element == "Action")
		{
			assert(data->mScope->Is(Entity::TypeIdClass()) || data->mScope->Is(Action::TypeIdClass()));
			if (mState != State::ParsingEntity && mState != State::ParsingAction)
			{
				throw exception("Attempting to parse an mAction when not in an mEntity");
			}

			mState = State::ParsingAction;
			string className = attributes.Find("ClassName")->second;
			string instanceName = attributes.Find("InstanceName")->second;

			Action* action = nullptr;

			if (data->mScope->Is(Entity::TypeIdClass()))
			{
				mPreviousState = State::ParsingEntity;
				Entity* entity = data->mScope->As<Entity>();
				action = entity->CreateAction(className, instanceName);

				if (action->Is(ActionListIf::TypeIdClass()))
				{
					ActionListIf* actionList = action->As<ActionListIf>();
					assert(actionList != nullptr);
					string condition = attributes.Find("Condition")->second;
					actionList->SetCondition(stoi(condition));
				}
			}
			
			else if (data->mScope->Is(Action::TypeIdClass()))
			{
				mPreviousState = State::ParsingAction;
				Action* parent = data->mScope->As<Action>();
				if (parent->Is(ActionListIf::TypeIdClass()))
				{
					if (instanceName == "Then")
					{
						action = parent->As<ActionListIf>()->CreateThenAction(className, instanceName);
					}
					else if (instanceName == "Else")
					{
						action = parent->As<ActionListIf>()->CreateElseAction(className, instanceName);
					}
				}

				else if (parent->Is(ActionList::TypeIdClass()))
				{
					action = parent->As<ActionList>()->CreateAction(className, instanceName);
				}
			}

			data->mScope = action;
		}

		return true;
	}

	bool XmlParseHelperEntity::EndElementHandler(XmlParseMaster::SharedData& sharedData, const string& element)
	{
		SharedDataScope* data = sharedData.As<SharedDataScope>();

		assert(data->Depth() > 0);
		if (data == nullptr) { return false; }

		if (element == "Integer")
		{
			assert(mState == State::ParsingInteger);
		}

		else if (element == "Float")
		{
			assert(mState == State::ParsingFloat);
		}

		else if (element == "Vector")
		{
			assert(mState == State::ParsingVector || mState == State::ParsingMatrix);
		}

		else if (element == "Matrix")
		{
			assert(mMatrixComponentCount == 4);
			stringstream ss;

			// String format: mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))
			ss << "mat4x4(";
			for (uint32_t i = 0; i < 4; i++)
			{
				ss << "(";
				for (uint32_t j = 0; j < 4; j++)
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
		}

		else if (element == "String")
		{
			assert(mState == State::ParsingString);
		}

		else if (element == "World")
		{
			mPreviousState = State::NotParsing;
			assert(mState == State::ParsingWorld);
			assert(data->mScope->GetParent() == nullptr);
		}

		else if (element == "Sector")
		{
			mPreviousState = State::ParsingWorld;
			assert(mState == State::ParsingSector);
			assert(data->mScope->GetParent() != nullptr);
			data->mScope = data->mScope->GetParent();
		}

		else if (element == "Entity")
		{
			mPreviousState = State::ParsingSector;
			assert(mState == State::ParsingEntity);
			assert(data->mScope->GetParent() != nullptr);
			data->mScope = data->mScope->GetParent();
		}

		else if (element == "Action")
		{
			assert(mState == State::ParsingAction || mState == State::ParsingEntity);
			assert(data->mScope->GetParent() != nullptr);
			if (data->mScope->GetParent()->Is(Action::TypeIdClass()))
			{
				mPreviousState = State::ParsingAction;
			}
			else if(data->mScope->GetParent()->Is(Entity::TypeIdClass()))
			{
				mPreviousState = State::ParsingEntity;
			}
			else
			{
				throw exception("Attempting to enter an invalid state after parsing mAction");
			}
			data->mScope = data->mScope->GetParent();
		}

		mState = mPreviousState;
		if (data->Depth() == 0) mState = State::NotParsing;
		return true;
	}

	string XmlParseHelperEntity::ToString() const
	{
		return "Xml Parse Helper Scope";
	}

	bool XmlParseHelperEntity::Equals(const RTTI* rhs) const
	{
		if (this == rhs) { return true; }
		if (rhs == nullptr) { return false; }

		XmlParseHelperEntity* rhsConverted = rhs->As<XmlParseHelperEntity>();
		return (rhsConverted != nullptr) ? operator==(*rhsConverted) : false;
	}

	bool XmlParseHelperEntity::operator==(const XmlParseHelperEntity& rhs) const
	{
		bool matricesEquivalent = true;
		for (uint32_t i = 0; i < 4; i++)
		{
			for (uint32_t j = 0; j < 4; j++)
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


