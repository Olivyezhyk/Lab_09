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
void CountPhysicsGrades_A(Student_A* p, const int N, int& count_5, int& count_4, int& count_3);
int CountPhysicsAndMathGrades_A(Student_A* p, const int N);

int main() {
    int N = 0;
    Student_A* students_A = nullptr;

    int choice;
    do {
        cout << "\nMENU:" << endl;
        cout << "1. Create student list" << endl;
        cout << "2. Print students" << endl;
        cout << "3. Count Physics grades" << endl;
        cout << "4. Count students with high Physics and Math grades" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (students_A) delete[] students_A;
            Create_A(students_A, N);
            break;
        case 2:
            if (students_A) Print_A(students_A, N);
            else cout << "No students available. Please create a list first." << endl;
            break;
        case 3: {
            if (students_A) {
                int count_5, count_4, count_3;
                CountPhysicsGrades_A(students_A, N, count_5, count_4, count_3);
                cout << "Physics grade distribution: 5 - " << count_5 << ", 4 - " << count_4 << ", 3 - " << count_3 << endl;
            }
            else {
                cout << "No students available. Please create a list first." << endl;
            }
            break;
        }
        case 4: {
            if (students_A) {
                int count = CountPhysicsAndMathGrades_A(students_A, N);
                cout << "Number of students with grades 4 or 5 in both Physics and Math: " << count << endl;
            }
            else {
                cout << "No students available. Please create a list first." << endl;
            }
            break;
        }
        case 5:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    delete[] students_A;
    return 0;
}

void Create_A(Student_A*& p, int& N) {
    cout << "Enter the number of students: ";
    cin >> N;
    p = new Student_A[N];
    int specialty;
    for (int i = 0; i < N; i++) {
        cout << "\nStudent #" << i + 1 << ":" << endl;
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
        cout << "Informatics grade: ";
        cin >> p[i].informatics_grade;
    }
}

void Print_A(Student_A* p, const int N) {
    cout << "\n===========================================================================================" << endl;
    cout << "| #   | Surname         | Course | Specialty               | Physics | Math | Informatics |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << left << i + 1 << " ";
        cout << "| " << setw(15) << left << p[i].surname << " | "
            << setw(6) << left << p[i].course << " | "
            << setw(23) << left << specialtyStr[p[i].specialty] << " | "
            << setw(7) << left << p[i].physics_grade << " | "
            << setw(4) << left << p[i].math_grade << " | "
            << setw(11) << left << p[i].informatics_grade << " |" << endl;
    }
    cout << "===========================================================================================" << endl;
}

void CountPhysicsGrades_A(Student_A* p, const int N, int& count_5, int& count_4, int& count_3) {
    count_5 = count_4 = count_3 = 0;
    for (int i = 0; i < N; i++) {
        if (p[i].physics_grade == 5) count_5++;
        else if (p[i].physics_grade == 4) count_4++;
        else if (p[i].physics_grade == 3) count_3++;
    }
}

int CountPhysicsAndMathGrades_A(Student_A* p, const int N) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if ((p[i].physics_grade >= 4) && (p[i].math_grade >= 4)) {
            count++;
        }
    }
    return count;
}
