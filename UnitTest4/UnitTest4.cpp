#include "pch.h"
#include "CppUnitTest.h"
#include "..\\Lab_09_02_B\\Lab_09_02_B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest4
{
	TEST_CLASS(UnitTest4)
	{
	public:

		TEST_METHOD(TestSortPhysicsGrade)
		{
			Student_B students[] = {
				{ "Smith", 1, COMPUTER_SCIENCE, 3, 4, 5 },
				{ "Johnson", 2, INFORMATICS, 5, 3, 5 },
				{ "Williams", 3, MATH_ECONOMICS, 4, 4, 5 },
				{ "Jones", 4, PHYSICS_INFORMATICS, 5, 5, 5 }
			};
			int N = 4;

			SortStudents_B(students, N);

			Assert::AreEqual(students[0].physics_grade, 5);
			Assert::AreEqual(students[1].physics_grade, 5);
			Assert::AreEqual(students[2].physics_grade, 4);
			Assert::AreEqual(students[3].physics_grade, 3);
		}

		TEST_METHOD(TestBinarySearch)
		{
			Student_B students[] = {
				{ "Smith", 1, COMPUTER_SCIENCE, 3, 4, 5 },
				{ "Johnson", 2, INFORMATICS, 5, 3, 5 },
				{ "Williams", 3, MATH_ECONOMICS, 4, 4, 5 },
				{ "Jones", 4, PHYSICS_INFORMATICS, 5, 5, 5 }
			};
			int N = 4;

			bool found = BinarySearch_B(students, N, "Smith", 1, 3);

			Assert::IsTrue(found);
		}

		TEST_METHOD(TestIndexSort)
		{
			Student_B students[] = {
				{ "Smith", 1, COMPUTER_SCIENCE, 3, 4, 5 },
				{ "Johnson", 2, INFORMATICS, 5, 3, 5 },
				{ "Williams", 3, MATH_ECONOMICS, 4, 4, 5 },
				{ "Jones", 4, PHYSICS_INFORMATICS, 5, 5, 5 }
			};
			int N = 4;

			int* sortedIndices = IndexSort_B(students, N);

			Assert::AreEqual(sortedIndices[0], 1);
			Assert::AreEqual(sortedIndices[1], 3);
			Assert::AreEqual(sortedIndices[2], 2);
			Assert::AreEqual(sortedIndices[3], 0);

			delete[] sortedIndices;
		}
	};
}
