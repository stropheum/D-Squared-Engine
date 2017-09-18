#pragma once

namespace TestLibraryDesktop
{
	class LeakDetector
	{

	public:

#pragma region Construction/Assignment/Move Semantics

		LeakDetector() = delete;

		~LeakDetector() = delete;

		LeakDetector(const LeakDetector& rhs) = delete;

		LeakDetector& operator=(const LeakDetector& rhs) = delete;

		LeakDetector(LeakDetector&& rhs) = delete;

		LeakDetector& operator=(LeakDetector&& rhs) = delete;

#pragma endregion

		static void InitializeLeakDetection();

		static void FinalizeLeakDetection();

	private:

		static _CrtMemState sStartMemState;

	};
}