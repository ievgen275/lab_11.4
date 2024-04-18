#include "pch.h"
#include "CppUnitTest.h"
#include "../PR_11.4/PR_11.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(CompareByName_LessThan_ReturnsTrue)
		{
			Tovar a = { "A", 20.0, 10, "kg" };
			Tovar b = { "B", 30.0, 15, "units" };

			bool result = CompareByName(a, b);

			Assert::IsTrue(result);
		}

		TEST_METHOD(CompareByName_GreaterThan_ReturnsFalse)
		{
			Tovar a = { "B", 30.0, 15, "units" };
			Tovar b = { "A", 20.0, 10, "kg" };

			bool result = CompareByName(a, b);

			Assert::IsFalse(result);
		}
	};
}
