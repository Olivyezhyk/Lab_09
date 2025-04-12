#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

enum Specialty { COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS, PHYSICS_INFORMATICS, TECHNICAL_EDUCATION };
string specialtyStr[] = { "Computer Science", "Informatics", "Math and Economics", "Physics and Informatics", "Technical Education" };

struct Student_A {
    string surname;
    int course;
    Specialty specialty;
    int physics_grade;
    int math_grade;
    int informatics_grade;
};

void Create_A(Student_A*& p, int& N);
void Print_A(Student_A* p, const int N);
void SortStudents_A(Student_A* p, const int N);
int* IndexSort_A(Student_A* p, const int N);
void PrintIndexSorted_A(Student_A* p, int* I, const int N);
bool BinarySearch_A(Student_A* p, const int N, const std::string& surname, int course, int physics_grade);

int main() {
    Student_A* students_A = nullptr;
    int N = 0;
    int choice;
    do {
        cout << "\nMENU:" << endl;
        cout << "1. Create student list" << endl;
        cout << "2. Print students" << endl;
        cout << "3. Sort students physically" << endl;
        cout << "4. Sort students by index" << endl;
        cout << "5. Binary search student" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            Create_A(students_A, N);
            break;
        case 2:
            if (N > 0) Print_A(students_A, N);
            else cout << "No students available!\n";
            break;
        case 3:
            SortStudents_A(students_A, N);
            Print_A(students_A, N);
            break;

        case 4: {
            int* I_A = IndexSort_A(students_A, N);
            PrintIndexSorted_A(students_A, I_A, N);
            delete[] I_A;
            break;
        }
        case 5: {
            string searchSurname;
            int searchCourse, searchPhysicsGrade;
            cout << "Enter surname: ";
            cin >> searchSurname;
            cout << "Enter course: ";
            cin >> searchCourse;
            cout << "Enter physics grade: ";
            cin >> searchPhysicsGrade;

            bool found = BinarySearch_A(students_A, N, searchSurname, searchCourse, searchPhysicsGrade);
            cout << (found ? "Student found!\n" : "Student not found!\n");
            break;
        }
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    delete[] students_A;
    return 0;
}

void Create_A(Student_A*& p, int& N) {
    cout << "Enter number of students: ";
    cin >> N;
    p = new Student_A[N];

    for (int i = 0; i < N; i++) {
        cout << "\nStudent #" << i + 1 << ":" << endl;
        cout << "Surname: ";
        cin >> p[i].surname;
        cout << "Course: ";
        cin >> p[i].course;
        cout << "Specialty (0 - Computer Science, 1 - Informatics, 2 - Math and Economics, 3 - Physics and Informatics, 4 - Technical Education): ";
        int spec;
        cin >> spec;
        p[i].specialty = static_cast<Specialty>(spec);
        cout << "Physics grade: ";
        cin >> p[i].physics_grade;
        cout << "Math grade: ";
        cin >> p[i].math_grade;
        cout << "Informatics grade: ";
        cin >> p[i].informatics_grade;
    }
}

void Print_A(Student_A* p, const int N) {
    cout << "\n===========================================================================================" << endl;
    cout << "| #   | Surname         | Course | Specialty               | Physics | Math | Informatics |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << left << i + 1 << " "
            << "| " << setw(15) << left << p[i].surname << " | "
            << setw(6) << left << p[i].course << " | "
            << setw(23) << left << specialtyStr[p[i].specialty] << " | "
            << setw(7) << left << p[i].physics_grade << " | "
            << setw(4) << left << p[i].math_grade << " | "
            << setw(11) << left << p[i].informatics_grade << " |" << endl;
    }
    cout << "===========================================================================================" << endl;
}

void PrintIndexSorted_A(Student_A* p, int* I, const int N) {
    cout << "\n===========================================================================================" << endl;
    cout << "| #   | Surname         | Course | Specialty               | Physics | Math | Informatics |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << left << i + 1 << " "
            << "| " << setw(15) << left << p[I[i]].surname << " | "
            << setw(6) << left << p[I[i]].course << " | "
            << setw(23) << left << specialtyStr[p[I[i]].specialty] << " | "
            << setw(7) << left << p[I[i]].physics_grade << " | "
            << setw(4) << left << p[I[i]].math_grade << " | "
            << setw(11) << left << p[I[i]].informatics_grade << " |" << endl;
    }
    cout << "===========================================================================================" << endl;
}


void SortStudents_A(Student_A* p, const int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (p[j].physics_grade < p[j + 1].physics_grade ||
                (p[j].physics_grade == p[j + 1].physics_grade && p[j].course > p[j + 1].course) ||
                (p[j].physics_grade == p[j + 1].physics_grade && p[j].course == p[j + 1].course && p[j].surname < p[j + 1].surname)) {
                swap(p[j], p[j + 1]);
            }
        }
    }
}

int* IndexSort_A(Student_A* p, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++) {
        I[i] = i;
    }

    for (int i = 1; i < N; i++) {
        int value = I[i];
        int j = i - 1;
        while (j >= 0 && (p[I[j]].physics_grade < p[value].physics_grade ||
            (p[I[j]].physics_grade == p[value].physics_grade && p[I[j]].course > p[value].course) ||
            (p[I[j]].physics_grade == p[value].physics_grade && p[I[j]].course == p[value].course && p[I[j]].surname > p[value].surname))) {
            I[j + 1] = I[j];
            j--;
        }
        I[j + 1] = value;
    }
    return I;
}

bool BinarySearch_A(Student_A* p, const int N, const std::string& surname, int course, int physics_grade) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (p[mid].physics_grade == physics_grade && p[mid].course == course && p[mid].surname == surname) {
            return true;
        }
        else if (p[mid].physics_grade > physics_grade ||
            (p[mid].physics_grade == physics_grade && p[mid].course < course) ||
            (p[mid].physics_grade == physics_grade && p[mid].course == course && p[mid].surname < surname)) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return false;
}
