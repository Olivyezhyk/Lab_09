#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_09_03/Lab_09_03.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest5
{
    TEST_CLASS(UnitTest5)
    {
    public:

        TEST_METHOD(TestSearchByPhone)
        {
            Note notes[MAX_NOTES];
            int N = 3;

            notes[0] = { "Smith", "John", "123456789", {1, 1, 2000} };
            notes[1] = { "Doe", "Jane", "987654321", {15, 5, 1995} };
            notes[2] = { "Black", "Alice", "555555555", {10, 3, 1998} };

            string phone = "987654321";
            Note* result = searchByPhone(notes, N, phone);

            Assert::IsNotNull(result);
            Assert::AreEqual("Doe", result->surname.c_str());
            Assert::AreEqual("Jane", result->name.c_str());
            Assert::AreEqual("987654321", result->phone.c_str());
        }

        TEST_METHOD(TestSortNotesByBirthday)
        {
            Note notes[MAX_NOTES];
            int N = 3;

            notes[0] = { "Smith", "John", "123456789", {1, 1, 2000} };
            notes[1] = { "Doe", "Jane", "987654321", {15, 5, 1995} };
            notes[2] = { "Black", "Alice", "555555555", {10, 3, 1998} };

            sortNotesByBirthday(notes, N);

            Assert::AreEqual("Doe", notes[0].surname.c_str());
            Assert::AreEqual("Black", notes[1].surname.c_str());
            Assert::AreEqual("Smith", notes[2].surname.c_str());
        }

        TEST_METHOD(TestSaveAndLoad)
        {
            Note notes[MAX_NOTES];
            int N = 3;

            notes[0] = { "Smith", "John", "123456789", {1, 1, 2000} };
            notes[1] = { "Doe", "Jane", "987654321", {15, 5, 1995} };
            notes[2] = { "Black", "Alice", "555555555", {10, 3, 1998} };

            string filename = "test_data.bin";
            saveToFile(notes, N, filename);

            Note loadedNotes[MAX_NOTES];
            int loadedCount = 0;
            loadFromFile(loadedNotes, loadedCount, filename);

            Assert::AreEqual(N, loadedCount);
            Assert::AreEqual("Smith", loadedNotes[0].surname.c_str());
            Assert::AreEqual("Doe", loadedNotes[1].surname.c_str());
            Assert::AreEqual("Black", loadedNotes[2].surname.c_str());
        }
    };
}
