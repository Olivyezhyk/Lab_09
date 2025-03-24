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
void Sort_B(Student_B* p, const int N, int criterion);
int* IndexSort_B(Student_B* p, const int N);
void PrintIndexSorted_B(Student_B* p, int* I, const int N);
bool CompareStudents_B(const Student_B& a, const Student_B& b);
bool BinarySearch_B(Student_B* p, const int N, const string& surname, int course, int physics_grade);

int ChooseSortCriteria() {
    int choice;
    cout << "Select sorting criteria:" << endl;
    cout << "1. Sort by Physics grade" << endl;
    cout << "2. Sort by Course" << endl;
    cout << "3. Sort by Surname (descending)" << endl;
    cout << "Enter your choice (1/2/3): ";
    cin >> choice;
    return choice;
}

int main() {

    int N;
    cout << "Enter the number of students: ";
    cin >> N;

    Student_B* students_B = new Student_B[N];
    Create_B(students_B, N);
    int sortCriterion = ChooseSortCriteria();
    Sort_B(students_B, N, sortCriterion);
    cout << endl;
    Print_B(students_B, N);

    cout << endl;
    cout << "Index Sorting: " << endl;
    int* I_B = IndexSort_B(students_B, N);
    PrintIndexSorted_B(students_B, I_B, N);
    delete[] I_B;
    cout << endl;

    string searchSurnameB;
    int searchCourseB, searchPhysicsGradeB;

    cout << "Enter surname to search: ";
    cin >> searchSurnameB;
    cout << "Enter course: ";
    cin >> searchCourseB;
    cout << "Enter physics grade: ";
    cin >> searchPhysicsGradeB;

    bool foundB = BinarySearch_B(students_B, N, searchSurnameB, searchCourseB, searchPhysicsGradeB);
    if (foundB) {
        cout << "Student found in Student!" << endl;
    }
    else {
        cout << "Student not found in Student!" << endl;
    }
    cout << endl;

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
        cout << endl;
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

void Sort_B(Student_B* p, const int N, int criterion) {
    Student_B tmp;
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            bool swap = false;
            if (criterion == 1) {
                if ((p[j].physics_grade < p[j + 1].physics_grade)) {
                    swap = true;
                }
            }
            else if (criterion == 2) {
                if (p[j].course > p[j + 1].course) {
                    swap = true;
                }
            }
            else if (criterion == 3) {
                if (p[j].surname < p[j + 1].surname) {
                    swap = true;
                }
            }

            if (swap) {
                tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
    }
}

int* IndexSort_B(Student_B* p, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++) {
        I[i] = i;
    }

    int i, j, value;
    for (i = 1; i < N; i++) {
        value = I[i];
        for (j = i - 1; j >= 0 &&
            (p[I[j]].physics_grade < p[value].physics_grade ||
                (p[I[j]].physics_grade == p[value].physics_grade && p[I[j]].course > p[value].course) ||
                (p[I[j]].physics_grade == p[value].physics_grade && p[I[j]].course == p[value].course && p[I[j]].surname > p[value].surname)); j--) {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted_B(Student_B* p, int* I, const int N) {
    cout << endl;
    cout << "===========================================================================================================================" << endl;
    cout << "| #   | Surname         | Course | Specialty                | Physics | Math | Programming | Numerical Methods | Pedagogy |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {

        int idx = I[i];

        cout << "| " << setw(3) << left << i + 1 << " ";
        cout << "| " << setw(15) << left << p[idx].surname << " | "
            << setw(6) << left << p[idx].course << " | "
            << setw(24) << left << specialtyStr[p[idx].specialty] << " | "
            << setw(7) << left << p[idx].physics_grade << " | "
            << setw(4) << left << p[idx].math_grade << " | ";

        switch (p[idx].specialty) {
        case COMPUTER_SCIENCE:
            cout << setw(11) << left << p[idx].programming_grade << " | ";
            cout << setw(17) << left << " " << " | ";
            cout << setw(8) << left << " " << " | ";
            break;
        case INFORMATICS:
            cout << setw(11) << left << " " << " | ";
            cout << setw(17) << left << p[idx].numerical_methods_grade << " | ";
            cout << setw(8) << left << " " << " | ";
            break;
        default:
            cout << setw(11) << left << " " << " | ";
            cout << setw(17) << left << " " << " | ";
            cout << setw(8) << left << p[idx].pedagogy_grade << " | ";
            break;
        }

        cout << endl;
    }
    cout << "===========================================================================================================================" << endl;
    cout << endl;
}

bool CompareStudents_B(const Student_B& a, const Student_B& b) {
    if (a.surname != b.surname) return a.surname < b.surname;
    if (a.course != b.course) return a.course < b.course;
    return a.physics_grade < b.physics_grade;
}


bool BinarySearch_B(Student_B* p, const int N, const string& surname, int course, int physics_grade) {
    int left = 0, right = N - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (p[mid].surname == surname && p[mid].course == course && p[mid].physics_grade == physics_grade) {
            return true;
        }

        if (CompareStudents_B(p[mid], Student_B{ surname, course, {}, physics_grade, 0, 0 })) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return false;
}