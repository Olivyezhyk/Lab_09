#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_NOTES = 100;

struct Note {
    string surname;
    string name;
    string phone;
    int birthDate[3];
};

void inputNotes(Note notes[], int& N);
void displayNotes(const Note notes[], int N);
void sortNotesByBirthday(Note notes[], int N);
Note* searchByPhone(Note notes[], int N, const string& phone);
void saveToFile(Note notes[], int N, const string& filename);
void loadFromFile(Note notes[], int& N, const string& filename);

int main() {
    Note notes[MAX_NOTES];
    int N = 0;
    int menuItem;
    string phone, filename;

    do {
        cout << "Menu:" << endl;
        cout << "1 - Input data" << endl;
        cout << "2 - Display data" << endl;
        cout << "3 - Sort by birthday" << endl;
        cout << "4 - Search by phone number" << endl;
        cout << "5 - Save to file" << endl;
        cout << "6 - Load from file" << endl;
        cout << "0 - Exit" << endl;
        cout << endl;
        cout << "Your choice: ";
        cin >> menuItem;
        cin.ignore();

        switch (menuItem) {
        case 1:
            cout << endl;
            cout << "Enter the number of records: ";
            cin >> N;
            cin.ignore();
            inputNotes(notes, N);
            cout << endl;
            break;
        case 2:
            cout << endl;
            displayNotes(notes, N);
            cout << endl;
            break;
        case 3:
            cout << endl;
            sortNotesByBirthday(notes, N);
            cout << "Data sorted." << endl;
            cout << endl;
            break;
        case 4:
            cout << endl;
            cout << "Enter phone number: ";
            getline(cin, phone);
            if (Note* found = searchByPhone(notes, N, phone)) {
                cout << "Found: " << found->surname << " " << found->name << " " << found->birthDate[0] << "." << found->birthDate[1] << "." << found->birthDate[2] << endl;
            }
            else {
                cout << "Record not found." << endl;
            }
            cout << endl;
            break;
        case 5:
            cout << endl;
            cout << "Enter filename: ";
            getline(cin, filename);
            saveToFile(notes, N, filename);
            cout << endl;
            break;
        case 6:
            cout << endl;
            cout << "Enter filename: ";
            getline(cin, filename);
            loadFromFile(notes, N, filename);
            cout << "Loaded data:" << endl;
            displayNotes(notes, N);
            cout << endl;
            break;
        case 0:
            break;
        default:
            cout << "Error! Enter a valid number." << endl;
        }
    } while (menuItem != 0);

    return 0;
}

void inputNotes(Note notes[], int& N) {
    for (int i = 0; i < N; ++i) {
        cout << endl;
        cout << "Record " << i + 1 << ":" << endl;
        cout << "Surname: "; getline(cin, notes[i].surname);
        cout << "Name: "; getline(cin, notes[i].name);
        cout << "Phone number: "; getline(cin, notes[i].phone);
        cout << "Birthdate (day month year): ";
        cin >> notes[i].birthDate[0] >> notes[i].birthDate[1] >> notes[i].birthDate[2];
        cin.ignore();
    }
}

void displayNotes(const Note notes[], int N) {
    cout << left << setw(15) << "Surname" << setw(15) << "Name" << setw(15) << "Phone" << "Birthdate" << endl;
    for (int i = 0; i < N; ++i) {
        cout << left << setw(15) << notes[i].surname << setw(15) << notes[i].name
            << setw(15) << notes[i].phone << notes[i].birthDate[0] << "." << notes[i].birthDate[1] << "." << notes[i].birthDate[2] << endl;
    }
}

void sortNotesByBirthday(Note notes[], int N) {
    for (int i = 0; i < N - 1; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if ((notes[j].birthDate[2] < notes[i].birthDate[2]) ||
                (notes[j].birthDate[2] == notes[i].birthDate[2] && notes[j].birthDate[1] < notes[i].birthDate[1]) ||
                (notes[j].birthDate[2] == notes[i].birthDate[2] && notes[j].birthDate[1] == notes[i].birthDate[1] && notes[j].birthDate[0] < notes[i].birthDate[0])) {
                swap(notes[i], notes[j]);
            }
        }
    }
}

Note* searchByPhone(Note notes[], int N, const string& phone) {
    for (int i = 0; i < N; ++i) {
        if (notes[i].phone == phone) {
            return &notes[i];
        }
    }
    return nullptr;
}

void saveToFile(Note notes[], int N, const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    fout << N << '\n';
    for (int i = 0; i < N; i++) {
        fout << notes[i].surname << '\n' << notes[i].name << '\n' << notes[i].phone << '\n';
        fout << notes[i].birthDate[0] << ' ' << notes[i].birthDate[1] << ' ' << notes[i].birthDate[2] << '\n';
    }
}

void loadFromFile(Note notes[], int& N, const string& filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Failed to open the file!" << endl;
        return;
    }

    fin >> N;
    fin.ignore();
    if (N > MAX_NOTES) {
        cerr << "Error: Too many records in file!" << endl;
        N = 0;
        return;
    }

    for (int i = 0; i < N; i++) {
        getline(fin, notes[i].surname);
        getline(fin, notes[i].name);
        getline(fin, notes[i].phone);
        fin >> notes[i].birthDate[0] >> notes[i].birthDate[1] >> notes[i].birthDate[2];
        fin.ignore();
    }
}