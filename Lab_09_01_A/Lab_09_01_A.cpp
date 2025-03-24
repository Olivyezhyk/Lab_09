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

void Create_A(Student_A* p, const int N);
void Print_A(Student_A* p, const int N);
void CountPhysicsGrades_A(Student_A* p, const int N);
void CountPhysicsAndMathGrades_A(Student_A* p, const int N);

int main() {
    int N;
    cout << "Enter the number of students: ";
    cin >> N;

    Student_A* students_A = new Student_A[N];
    Create_A(students_A, N);
    Print_A(students_A, N);

    CountPhysicsGrades_A(students_A, N);
    CountPhysicsAndMathGrades_A(students_A, N);

    delete[] students_A;
    return 0;
}

void Create_A(Student_A* p, const int N) {
    int specialty;
    for (int i = 0; i < N; i++) {
        cout << endl;
        cout << "Student #" << i + 1 << ":" << endl;
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
    cout << endl;
    cout << "===========================================================================================" << endl;
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
    cout << endl;
}

void CountPhysicsGrades_A(Student_A* p, const int N) {
    int count_5 = 0, count_4 = 0, count_3 = 0;
    for (int i = 0; i < N; i++) {
        if (p[i].physics_grade == 5) count_5++;
        else if (p[i].physics_grade == 4) count_4++;
        else if (p[i].physics_grade == 3) count_3++;
    }
    cout << "Physics grade distribution: 5 - " << count_5 << ", 4 - " << count_4 << ", 3 - " << count_3 << endl;
}

void CountPhysicsAndMathGrades_A(Student_A* p, const int N) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if ((p[i].physics_grade >= 4) && (p[i].math_grade >= 4)) {
            count++;
        }
    }
    cout << "Number of students with grades 4 or 5 in both Physics and Math: " << count << endl;
}