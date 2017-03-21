#pragma once
#include "Vector.h"
#include <expat.h>


namespace Library
{
	class IXmlParseHelper;
	class XmlParseMaster
	{
	public:

#pragma region SharedData Implementation
		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData, RTTI)
		public:
			SharedData(): mParseMaster(nullptr), mDepth(0) {}
			
			virtual SharedData* clone() = 0;

			void setXmlParseMaster(XmlParseMaster* const parseMaster)
			{
				mParseMaster = parseMaster;
			}

			XmlParseMaster* getXmlParseMaster() const
			{
				return mParseMaster;
			}

			XmlParseMaster* getXmlParaseMaster() const
			{
				return const_cast<XmlParseMaster* const>(mParseMaster);
			}

			void incrementDepth()
			{
				mDepth++;
			}

			void decrementDepth()
			{
				mDepth--;
			}

			std::uint32_t depth() const
			{
				return mDepth;
			}

			virtual std::string ToString() const override
			{
				return "Shared Data";
			}

			virtual bool Equals(const RTTI* rhs) const override
			{
				if (this == rhs)
				{
					return true;
				}

				const SharedData* data = rhs->As<SharedData>();
				bool result = false;

				if (data != nullptr)
				{
					result = (this == rhs);
				}

				return result;
			}

		protected:
			XmlParseMaster* mParseMaster;
			std::uint32_t mDepth;
		};
#pragma endregion

		explicit XmlParseMaster(SharedData* const sharedData);
		virtual ~XmlParseMaster();

		virtual XmlParseMaster* clone() const;
		void addHelper(IXmlParseHelper& helper);
		void removeHelper(IXmlParseHelper& helper);
		void parse(char* const xmlData, const std::uint32_t length, const bool endOfFile) const;
		void parse(const std::string xmlData, const std::uint32_t length, const bool endOfFile) const;
		void parseFromFile(std::string fileName);
		const std::string& getFileName() const;
		void setSharedData(SharedData* const sharedData);
		SharedData* getSharedData() const;

	private:
		static void startElementHandler(void *userData, const XML_Char *name, const XML_Char **atts);
		static void endElementHandler(void *userData, const XML_Char *name);
		static void charDataHandler(void *userData, const XML_Char *s, int len);

		XML_Parser mXmlParser;
		std::string mActiveFileName;
		SharedData* mSharedData;
		Vector<IXmlParseHelper*> mHelpers;
		std::uint32_t mDepth;
		bool mClonedInstance;
	};
}

