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
void Sort_A(Student_A* p, const int N, int criterion);
int* IndexSort_A(Student_A* p, const int N);
void PrintIndexSorted_A(Student_A* p, int* I, const int N);
bool CompareStudents_A(const Student_A& a, const Student_A& b);
bool BinarySearch_A(Student_A* p, const int N, const string& surname, int course, int physics_grade);

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

    cout << endl;
    Student_A* students_A = new Student_A[N];
    Create_A(students_A, N);
    int sortCriterion = ChooseSortCriteria();
    Sort_A(students_A, N, sortCriterion);
    cout << endl;
    Print_A(students_A, N);

    cout << endl;
    cout << "Index Sorting: " << endl;
    int* I_A = IndexSort_A(students_A, N);
    PrintIndexSorted_A(students_A, I_A, N);
    delete[] I_A;
    cout << endl;

    string searchSurnameA;
    int searchCourseA, searchPhysicsGradeA;

    cout << "Enter surname to search: ";
    cin >> searchSurnameA;
    cout << "Enter course: ";
    cin >> searchCourseA;
    cout << "Enter physics grade: ";
    cin >> searchPhysicsGradeA;

    bool foundA = BinarySearch_A(students_A, N, searchSurnameA, searchCourseA, searchPhysicsGradeA);
    if (foundA) {
        cout << "Student found in Student!" << endl;
    }
    else {
        cout << "Student not found in Student!" << endl;
    }
    cout << endl;

    delete[] students_A;

    return 0;
}

void Create_A(Student_A* p, const int N) {
    int specialty;
    for (int i = 0; i < N; i++) {
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
        cout << endl;
    }
}

void Print_A(Student_A* p, const int N) {
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
}

void Sort_A(Student_A* p, const int N, int criterion) {
    Student_A tmp;
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

int* IndexSort_A(Student_A* p, const int N) {
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

void PrintIndexSorted_A(Student_A* p, int* I, const int N) {
    cout << "===========================================================================================" << endl;
    cout << "| #   | Surname         | Course | Specialty               | Physics | Math | Informatics |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << left << i + 1 << " ";
        cout << "| " << setw(15) << left << p[I[i]].surname << " | "
            << setw(6) << left << p[I[i]].course << " | "
            << setw(23) << left << specialtyStr[p[I[i]].specialty] << " | "
            << setw(7) << left << p[I[i]].physics_grade << " | "
            << setw(4) << left << p[I[i]].math_grade << " | "
            << setw(11) << left << p[I[i]].informatics_grade << " |" << endl;
    }
    cout << "===========================================================================================" << endl;
}

bool CompareStudents_A(const Student_A& a, const Student_A& b) {
    if (a.surname != b.surname) return a.surname < b.surname;
    if (a.course != b.course) return a.course < b.course;
    return a.physics_grade < b.physics_grade;
}


bool BinarySearch_A(Student_A* p, const int N, const string& surname, int course, int physics_grade) {
    int left = 0, right = N - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (p[mid].surname == surname && p[mid].course == course && p[mid].physics_grade == physics_grade) {
            return true;
        }

        if (CompareStudents_A(p[mid], Student_A{ surname, course, {}, physics_grade, 0, 0 })) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return false;
}
