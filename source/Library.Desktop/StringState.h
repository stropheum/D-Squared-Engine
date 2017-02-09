#pragma once

namespace Library
{
	class StringState :
		public Library::TypeState
	{
	public:
		StringState(Datum* const context);
		~StringState();

		Datum& operator=(const std::string& rhs) override;

		void setSize(std::uint32_t size) override;
		void reserve(std::uint32_t capacity) override;
		void clear() override;
		void setFromString(const std::string& value, const std::uint32_t& index) override;
	};
}

