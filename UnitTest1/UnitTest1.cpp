#include "pch.h"
#include "CppUnitTest.h"
#include "..\\Lab_09_01_A\\Lab_09_01_A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestCountPhysicsGrades)
		{
			Student_A students[] = {
				{ "Smith", 1, COMPUTER_SCIENCE, 5, 4, 3 },
				{ "Johnson", 2, INFORMATICS, 4, 4, 4 },
				{ "Williams", 3, MATH_ECONOMICS, 3, 3, 3 },
				{ "Jones", 4, PHYSICS_INFORMATICS, 5, 5, 5 }
			};
			int N = 4;

			int count_5 = 0, count_4 = 0, count_3 = 0;
			for (int i = 0; i < N; i++) {
				if (students[i].physics_grade == 5) count_5++;
				else if (students[i].physics_grade == 4) count_4++;
				else if (students[i].physics_grade == 3) count_3++;
			}

			Assert::AreEqual(count_5, 2);
			Assert::AreEqual(count_4, 1);
			Assert::AreEqual(count_3, 1);
		}

		TEST_METHOD(TestCountPhysicsAndMathGrades)
		{
			Student_A students[] = {
				{ "Smith", 1, COMPUTER_SCIENCE, 5, 4, 3 },
				{ "Johnson", 2, INFORMATICS, 4, 4, 4 },
				{ "Williams", 3, MATH_ECONOMICS, 3, 3, 3 },
				{ "Jones", 4, PHYSICS_INFORMATICS, 5, 5, 5 }
			};
			int N = 4;

			int count = 0;
			for (int i = 0; i < N; i++) {
				if ((students[i].physics_grade >= 4) && (students[i].math_grade >= 4)) {
					count++;
				}
			}

			Assert::AreEqual(count, 3);
		}
	};
}
