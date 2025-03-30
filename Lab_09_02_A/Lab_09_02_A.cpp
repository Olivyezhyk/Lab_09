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
void SortStudents_A(Student_A* p, const int N, int sortOption);
int* IndexSort_A(Student_A* p, const int N);
void PrintIndexSorted_A(Student_A* p, int* I, const int N);
bool BinarySearch_A(Student_A* p, const int N, const std::string& surname, int course, int physics_grade, int sortOption);

int main() {
    int N;
    cout << "Enter the number of students: ";
    cin >> N;

    cout << endl;
    Student_A* students_A = new Student_A[N];
    Create_A(students_A, N);

    int sortOption;
    cout << "Choose sorting option (1 - by physics grade, 2 - by course, 3 - by surname): ";
    cin >> sortOption;
    SortStudents_A(students_A, N, sortOption);

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

    bool foundA = BinarySearch_A(students_A, N, searchSurnameA, searchCourseA, searchPhysicsGradeA, sortOption);
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

void SortStudents_A(Student_A* p, const int N, int sortOption) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            bool swapCondition = false;

            if (sortOption == 1) {
                if (p[j].physics_grade < p[j + 1].physics_grade) {
                    swapCondition = true;
                }
                else if (p[j].physics_grade == p[j + 1].physics_grade) {
                    if (p[j].course > p[j + 1].course) {
                        swapCondition = true;
                    }
                    else if (p[j].course == p[j + 1].course && p[j].surname < p[j + 1].surname) {
                        swapCondition = true;
                    }
                }
            }
            else if (sortOption == 2) {
                if (p[j].course > p[j + 1].course) {
                    swapCondition = true;
                }
                else if (p[j].course == p[j + 1].course) {
                    if (p[j].physics_grade < p[j + 1].physics_grade) {
                        swapCondition = true;
                    }
                    else if (p[j].physics_grade == p[j + 1].physics_grade && p[j].surname < p[j + 1].surname) {
                        swapCondition = true;
                    }
                }
            }
            else if (sortOption == 3) {
                if (p[j].surname < p[j + 1].surname) {
                    swapCondition = true;
                }
                else if (p[j].surname == p[j + 1].surname) {
                    if (p[j].course > p[j + 1].course) {
                        swapCondition = true;
                    }
                    else if (p[j].course == p[j + 1].course && p[j].physics_grade < p[j + 1].physics_grade) {
                        swapCondition = true;
                    }
                }
            }

            if (swapCondition) {
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

bool BinarySearch_A(Student_A* p, const int N, const std::string& surname, int course, int physics_grade, int sortOption) {
    int left = 0, right = N - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        bool match = false;

        if (sortOption == 1) {
            if (p[mid].physics_grade == physics_grade) {
                if (p[mid].course == course && p[mid].surname == surname) {
                    match = true;
                }
                else if (p[mid].course > course) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            else if (p[mid].physics_grade > physics_grade) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        else if (sortOption == 2) {
            if (p[mid].course == course) {
                if (p[mid].physics_grade == physics_grade && p[mid].surname == surname) {
                    match = true;
                }
                else if (p[mid].physics_grade > physics_grade) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            else if (p[mid].course < course) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        else if (sortOption == 3) {
            if (p[mid].surname == surname) {
                if (p[mid].course == course && p[mid].physics_grade == physics_grade) {
                    match = true;
                }
                else if (p[mid].course < course) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
            else if (p[mid].surname > surname) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        if (match) return true;
    }

    return false;
}

