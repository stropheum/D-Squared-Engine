#pragma once
#include "IXmlParseHelper.h"


namespace Library
{
	class XmlParseMaster
	{
	public:

#pragma region SharedData Implementation
		class SharedData
		{
		public:
			SharedData(): mParseMaster(nullptr), mDepth(0) {}
			
			SharedData* clone()
			{
				// TODO: Implement clone method
				return this;
			}

			void setXmlParseMaster(XmlParseMaster* const parseMaster)
			{
				UNREFERENCED_PARAMETER(parseMaster);
				// TODO: Implement method
			}

			XmlParseMaster* getXmlParseMaster()
			{
				return mParseMaster;
			}

			XmlParseMaster* const getXmlParaseMaster() const
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
				assert(mDepth >= 0);
			}

			std::uint32_t depth() const
			{
				return mDepth;
			}

		private:
			XmlParseMaster* mParseMaster;
			std::uint32_t mDepth;
		};
#pragma endregion

		XmlParseMaster();
		~XmlParseMaster();

		XmlParseMaster* clone();
		void addHelper(const IXmlParseHelper& helper);
		void removeHelper(const IXmlParseHelper& helper);
		void parse(char** xmlData, std::uint32_t length, bool endOfFile);
		void parseFromFile(std::string fileName);
		const std::string& getFileName() const;
		void setSharedData(SharedData* const sharedData);
		SharedData* const getSharedData() const;

	private:
		void startElementHandler();
		void endElementHandler();
		void charDataHandler();

		std::string mActiveFileName;
		SharedData* mSharedData;
	};
}

