#pragma once
#include "Vector.h"
#include <expat.h>
#include "RTTI.h"


namespace Library
{
	class IXmlParseHelper; // Friend class declaration for IXmlParseHelper

	class XmlParseMaster
	{

	public:

#pragma region SharedData Implementation

		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData, RTTI)

		public:
			
#pragma region SharedData Construction/Copy/Assignment
			
			SharedData(): mParseMaster(nullptr), mDepth(0) {}

			SharedData(const SharedData& rhs) = default;

			SharedData& operator=(const SharedData& rhs) = default;
			
			SharedData(SharedData&& rhs) = delete;

			SharedData& operator=(SharedData&& rhs) = delete;
			
#pragma endregion

			/**
			 * Clone method for Shared data
			 * @Return: A pointer to the freshly allocated Shared Data Clone. Client will be responsible for deleting it
			 */
			virtual SharedData* Clone() = 0;

			/**
			 * Setter for the Parse master associated with this shared data instance
			 * @Param parseMaster: The Parse master that will be associated with this shared data
			 */
			void SetXmlParseMaster(XmlParseMaster* const parseMaster)
			{
				mParseMaster = parseMaster;
			}

			/**
			 * Accessor for the Parse mater associated with this shared data instance
			 * @Retrun: The Parse master associated with this shared data
			 */
			XmlParseMaster* GetXmlParseMaster() const
			{
				return mParseMaster;
			}

			/**
			 * Increases the Depth value that the parser is currently operating At
			 */
			void IncrementDepth()
			{
				mDepth++;
			}

			/**
			 * Decreases the Depth value that the parser is currently operating At
			 */
			void DecrementDepth()
			{
				mDepth--;
			}

			/**
			 * Accessor method for the current Depth value that the parser is operating At
			 * @Return: The current depth of the parser
			 */
			std::uint32_t Depth() const
			{
				return mDepth;
			}

			/**
			 * RTTI ToString representation of the shared data class
			 * @Return: A string representation of the class Name
			 */
			std::string ToString() const override
			{
				return "Shared Data";
			}

			/**
			 * RTTI Equals comparison
			 * @Param rhs: The RTTI object being compared against
			 * @Return: True if the objects are shared data and identical pointers
			 */
			bool Equals(const RTTI* rhs) const override
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

#pragma region Construction/Copy/Assignment

		explicit XmlParseMaster(SharedData* const sharedData);

		virtual ~XmlParseMaster();

		explicit XmlParseMaster(const XmlParseMaster& rhs) = default;

		XmlParseMaster& operator=(const XmlParseMaster& rhs) = default;

		XmlParseMaster(XmlParseMaster&& rhs) = delete;

		XmlParseMaster& operator=(XmlParseMaster&& rhs) = delete;

#pragma endregion

		/**
		 * Clones the current Parse master by instantiating a new one with the same internal state
		 * @Return: A pointer to the new heap-allocated XmlParseMaster. User will be required to delete the pointer
		 */
		virtual XmlParseMaster* Clone() const;

		/**
		 * Adds a helper to the chain of responsibility
		 * @Param helper: The helper being added to the vector of helpers
		 */
		void AddHelper(IXmlParseHelper& helper);

		/**
		 * Removes a helper from the chain of responsibility
		 * @Param helper: The helper being removed from the vector of helpers
		 */
		void RemoveHelper(IXmlParseHelper& helper);

		/**
		 * Parses the passed in XML value by iterating through the chain of responsibility
		 * @Param xmlData: The string of xmlData being parsed
		 * @Param length: The number of characters in the xml data
		 * @Param endOfFile: Value used to determine if parsing has reached the end of the data. Used if chunking is utilized
		 */
		void Parse(char* const xmlData, const std::uint32_t& length, const bool endOfFile);

		/**
		 * Parses all xml data in the current file
		 * @Param fileName: The path of the file being parsed
		 */
		void ParseFromFile(const std::string& fileName);

		/**
		 * Accessor method for the Name of the file currently being parsed
		 * @Return: A string representing the current file being parsed
		 */
		const std::string& GetFileName() const;

		/**
		 * Setter method for the shared data associated with the Parse master
		 * @Param sharedData: The shared data object that will now be associated with the Parse master
		 */
		void SetSharedData(SharedData* const sharedData);

		/**
		 * Accessor method for the shared data associated with the Parse master
		 * @Return: The shared data object associated with the Parse master
		 */
		SharedData* GetSharedData() const;

	private:

		/**
		 * Callback method for Expat's start element handler
		 * @Param userData: The shared data that the handler will write to
		 * @Param Name: The Name of the entry being parsed
		 * @Param atts: The string,string pairs of attributes associated with the entry Name
		 */
		static void StartElementHandler(void *userData, const XML_Char *name, const XML_Char **atts);

		/**
		 * Callback method for Expat's end element handler
		 * @Param userData: The shared data that the handler will write to
		 * @Param Name: The Name of the entry being parsed
		 */
		static void EndElementHandler(void *userData, const XML_Char *name);

		/**
		 * Callback method for Expat's start element handler
		 * @Param userData: The shared data that the handler will write to
		 * @Param s: The character data being parsed
		 * @Param len: The number of characters being passed in s
		 */
		static void CharDataHandler(void *userData, const XML_Char *s, int len);

		/**
		 * Helper method to ensure that helpers are initialized properly before Parse calls
		 */
		void HandleHelperInitialization();

		XML_Parser mXmlParser; // The associated Expat parser object
		std::string mActiveFileName; // The file being parsed, if any
		SharedData* mSharedData; // The shared data that the Parse call will write to
		Vector<IXmlParseHelper*> mHelpers; // The collection of helpers in the chain of responsibility
		std::uint32_t mDepth; // How deep the scoping is in the current parsing level
		bool mClonedInstance; // This value is true if the Parse master was created via cloning. This means it is responsible for deleting its helpers and data
		bool mHelpersAreInitialized; // This value is true if the helpers have been properly initialized
	
	};
}

