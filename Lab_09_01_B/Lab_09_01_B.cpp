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

void Create_B(Student_B* p, const int N);
void Print_B(Student_B* p, const int N);
void CountPhysicsGrades_B(Student_B* p, const int N);
void CountPhysicsAndMathGrades_B(Student_B* p, const int N);

int main() {
    int N;
    cout << "Enter the number of students: ";
    cin >> N;

    Student_B* students_B = new Student_B[N];
    Create_B(students_B, N);
    Print_B(students_B, N);

    CountPhysicsGrades_B(students_B, N);
    CountPhysicsAndMathGrades_B(students_B, N);

    delete[] students_B;
    return 0;
}

void Create_B(Student_B* p, const int N) {
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

        switch (p[i].specialty) {
        case COMPUTER_SCIENCE:
            cout << "Programming grade: ";
            cin >> p[i].programming_grade;
            break;
        case INFORMATICS:
            cout << "Numerical methods grade: ";
            cin >> p[i].numerical_methods_grade;
            break;
        case MATH_ECONOMICS:
        case PHYSICS_INFORMATICS:
        case TECHNICAL_EDUCATION:
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

void CountPhysicsGrades_B(Student_B* p, const int N) {
    int count_5 = 0, count_4 = 0, count_3 = 0;
    for (int i = 0; i < N; i++) {
        if (p[i].physics_grade == 5) count_5++;
        else if (p[i].physics_grade == 4) count_4++;
        else if (p[i].physics_grade == 3) count_3++;
    }
    cout << "Physics grade distribution: 5 - " << count_5 << ", 4 - " << count_4 << ", 3 - " << count_3 << endl;
}

void CountPhysicsAndMathGrades_B(Student_B* p, const int N) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if ((p[i].physics_grade >= 4) && (p[i].math_grade >= 4)) {
            count++;
        }
    }
    cout << "Number of students with grades 4 or 5 in both Physics and Math: " << count << endl;
}