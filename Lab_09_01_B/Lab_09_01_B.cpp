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
void CountPhysicsGrades_B(Student_B* p, const int N, int& count_5, int& count_4, int& count_3);
int CountPhysicsAndMathGrades_B(Student_B* p, const int N);

int main() {
    int N = 0;
    Student_B* students_B = nullptr;

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
            if (students_B) delete[] students_B;
            Create_B(students_B, N);
            break;
        case 2:
            if (students_B) Print_B(students_B, N);
            else cout << "No students available. Please create a list first." << endl;
            break;
        case 3:
            if (students_B) {
                int count_5, count_4, count_3;
                CountPhysicsGrades_B(students_B, N, count_5, count_4, count_3);
                cout << "Physics grade distribution: 5 - " << count_5 << ", 4 - " << count_4 << ", 3 - " << count_3 << endl;
            }
            else {
                cout << "No students available. Please create a list first." << endl;
            }
            break;
        case 4:
            if (students_B) {
                int count = CountPhysicsAndMathGrades_B(students_B, N);
                cout << "Number of students with grades 4 or 5 in both Physics and Math: " << count << endl;
            }
            else {
                cout << "No students available. Please create a list first." << endl;
            }
            break;
        case 5:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    delete[] students_B;
    return 0;
}

void Create_B(Student_B*& p, int& N) {
    cout << "Enter the number of students: ";
    cin >> N;
    p = new Student_B[N];
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
    cout << "\n===========================================================================================================================" << endl;
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
}

void CountPhysicsGrades_B(Student_B* p, const int N, int& count_5, int& count_4, int& count_3) {
    count_5 = count_4 = count_3 = 0;
    for (int i = 0; i < N; i++) {
        if (p[i].physics_grade == 5) count_5++;
        else if (p[i].physics_grade == 4) count_4++;
        else if (p[i].physics_grade == 3) count_3++;
    }
}

int CountPhysicsAndMathGrades_B(Student_B* p, const int N) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if ((p[i].physics_grade >= 4) && (p[i].math_grade >= 4)) {
            count++;
        }
    }
    return count;
}
