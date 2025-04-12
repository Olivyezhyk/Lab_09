#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

enum Specialty { COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS, PHYSICS_INFORMATICS, TECHNICAL_EDUCATION };
string specialtyStr[] = { "Computer Science", "Informatics", "Math and Economics", "Physics and Informatics", "Technical Education" };

struct Student_B {
    string surname;
    int course;
    Specialty specialty;
    int physics_grade;
    int math_grade;
    union {
        int programming_grade;
        int numerical_methods_grade;
        int pedagogy_grade;
    };
};

void Create_B(Student_B*& p, int& N);
void Print_B(Student_B* p, const int N);
void SortStudents_B(Student_B* p, const int N);
int* IndexSort_B(Student_B* p, const int N);
void PrintIndexSorted_B(Student_B* p, int* I, const int N);
bool BinarySearch_B(Student_B* p, const int N, const std::string& surname, int course, int physics_grade);

int main() {
    Student_B* students_B = nullptr;
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
            Create_B(students_B, N);
            break;
        case 2:
            if (N > 0) Print_B(students_B, N);
            else cout << "No students available!\n";
            break;
        case 3:
            SortStudents_B(students_B, N);
            Print_B(students_B, N);
            break;

        case 4: {
            int* I_B = IndexSort_B(students_B, N);
            PrintIndexSorted_B(students_B, I_B, N);
            delete[] I_B;
            break;
        }
        case 5: {
            string searchSurname;
            int searchCourse, searchPhysicsGrade;
            cout << "\nEnter surname: ";
            cin >> searchSurname;
            cout << "Enter course: ";
            cin >> searchCourse;
            cout << "Enter physics grade: ";
            cin >> searchPhysicsGrade;

            bool found = BinarySearch_B(students_B, N, searchSurname, searchCourse, searchPhysicsGrade);
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

    delete[] students_B;
    return 0;
}


void Create_B(Student_B*& p, int& N) {
    cout << "Enter the number of students: ";
    cin >> N;
    p = new Student_B[N];

    int specialty;
    for (int i = 0; i < N; i++) {
        cout << endl << "Student #" << i + 1 << ":" << endl;
        cin.ignore();
        cout << "Surname: ";
        getline(cin, p[i].surname);
        cout << "Course: ";
        cin >> p[i].course;
        cout << "Specialty (0 - Computer Science, 1 - Informatics, 2 - Math and Economics, 3 - Physics and Informatics, 4 - Technical Education): ";
        cin >> specialty;
        p[i].specialty = static_cast<Specialty>(specialty);
        cout << "Physics grade: ";
        cin >> p[i].physics_grade;
        cout << "Math grade: ";
        cin >> p[i].math_grade;

        switch (p[i].specialty) {
        case COMPUTER_SCIENCE:
            cout << "Programming grade: ";
            cin >> p[i].programming_grade;
            break;
        case INFORMATICS:
            cout << "Numerical methods grade: ";
            cin >> p[i].numerical_methods_grade;
            break;
        default:
            cout << "Pedagogy grade: ";
            cin >> p[i].pedagogy_grade;
            break;
        }
    }
}


void Print_B(Student_B* p, const int N) {
    cout << endl;
    cout << "===========================================================================================================================" << endl;
    cout << "| #   | Surname         | Course | Specialty                | Physics | Math | Programming | Numerical Methods | Pedagogy |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << left << i + 1 << " ";
        cout << "| " << setw(15) << left << p[i].surname << " | "
            << setw(6) << left << p[i].course << " | "
            << setw(24) << left << specialtyStr[p[i].specialty] << " | "
            << setw(7) << left << p[i].physics_grade << " | "
            << setw(4) << left << p[i].math_grade << " | ";

        switch (p[i].specialty) {
        case COMPUTER_SCIENCE:
            cout << setw(11) << left << p[i].programming_grade << " | ";
            cout << setw(17) << left << " " << " | ";
            cout << setw(8) << left << " " << " | ";
            break;
        case INFORMATICS:
            cout << setw(11) << left << " " << " | ";
            cout << setw(17) << left << p[i].numerical_methods_grade << " | ";
            cout << setw(8) << left << " " << " | ";
            break;
        default:
            cout << setw(11) << left << " " << " | ";
            cout << setw(17) << left << " " << " | ";
            cout << setw(8) << left << p[i].pedagogy_grade << " | ";
            break;
        }

        cout << endl;
    }
    cout << "===========================================================================================================================" << endl;
    cout << endl;
}

void PrintIndexSorted_B(Student_B* p, int* I, const int N) {
    cout << "\n===========================================================================================================================" << endl;
    cout << "| #   | Surname         | Course | Specialty                | Physics | Math | Programming | Numerical Methods | Pedagogy |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << left << i + 1 << " ";
        cout << "| " << setw(15) << left << p[I[i]].surname << " | "
            << setw(6) << left << p[I[i]].course << " | "
            << setw(24) << left << specialtyStr[p[I[i]].specialty] << " | "
            << setw(7) << left << p[I[i]].physics_grade << " | "
            << setw(4) << left << p[I[i]].math_grade << " | ";

        switch (p[I[i]].specialty) {
        case COMPUTER_SCIENCE:
            cout << setw(11) << left << p[I[i]].programming_grade << " | ";
            cout << setw(17) << left << " " << " | ";
            cout << setw(8) << left << " " << " | ";
            break;
        case INFORMATICS:
            cout << setw(11) << left << " " << " | ";
            cout << setw(17) << left << p[I[i]].numerical_methods_grade << " | ";
            cout << setw(8) << left << " " << " | ";
            break;
        default:
            cout << setw(11) << left << " " << " | ";
            cout << setw(17) << left << " " << " | ";
            cout << setw(8) << left << p[I[i]].pedagogy_grade << " | ";
            break;
        }

        cout << endl;
    }
    cout << "===========================================================================================================================" << endl;
    cout << endl;
}

void SortStudents_B(Student_B* p, const int N) {
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

int* IndexSort_B(Student_B* p, const int N) {
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

bool BinarySearch_B(Student_B* p, const int N, const std::string& surname, int course, int physics_grade) {
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
