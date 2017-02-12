#pragma once

namespace Library
{
	class StringState :
		public Library::TypeState
	{
	public:
		explicit StringState(Datum* const context);

		Datum& operator=(const std::string& rhs) override;

		void setSize(std::uint32_t size) override;
		void reserve(std::uint32_t capacity) override;
		void clear() override;
		void setFromString(const std::string& value, const std::uint32_t& index) override;
		void setStorage(const Datum& rhs) override;
		void setStorage(std::string* data, std::uint32_t size) override;
		std::string toString(std::uint32_t index = 0) override;
	};
}

