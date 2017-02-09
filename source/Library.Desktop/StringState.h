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
	};
}

