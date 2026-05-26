#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <vector>
using namespace std;

// ─────────────────────────────────────────
//  Student Structure
// ─────────────────────────────────────────
struct Student {
    int    id;
    string name;
    int    age;
    string branch;
    float  gpa;
};

// ─────────────────────────────────────────
//  File I/O helpers
// ─────────────────────────────────────────
const string FILE_NAME = "students.dat";

void saveStudents(const vector<Student>& students) {
    ofstream out(FILE_NAME, ios::trunc);
    if (!out) {
        cerr << "  [ERROR] Cannot open file for writing.\n";
        return;
    }
    for (const auto& s : students) {
        out << s.id    << "\n"
            << s.name  << "\n"
            << s.age   << "\n"
            << s.branch << "\n"
            << s.gpa   << "\n";
    }
    out.close();
}

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream in(FILE_NAME);
    if (!in) return students;          // file may not exist yet

    Student s;
    while (in >> s.id) {
        in.ignore();
        getline(in, s.name);
        in >> s.age;
        in.ignore();
        getline(in, s.branch);
        in >> s.gpa;
        in.ignore();
        students.push_back(s);
    }
    in.close();
    return students;
}

// ─────────────────────────────────────────
//  ID helpers
// ─────────────────────────────────────────
bool idExists(const vector<Student>& students, int id) {
    for (const auto& s : students)
        if (s.id == id) return true;
    return false;
}

int findIndex(const vector<Student>& students, int id) {
    for (int i = 0; i < (int)students.size(); ++i)
        if (students[i].id == id) return i;
    return -1;
}

// ─────────────────────────────────────────
//  UI helpers
// ─────────────────────────────────────────
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printHeader(const string& title) {
    cout << "\n  ╔══════════════════════════════════════╗\n";
    cout <<   "  ║  " << left << setw(36) << title << "║\n";
    cout <<   "  ╚══════════════════════════════════════╝\n";
}

void printStudentRow(const Student& s) {
    cout << "  ┌─────────────────────────────────────────\n";
    cout << "  │  ID     : " << s.id     << "\n";
    cout << "  │  Name   : " << s.name   << "\n";
    cout << "  │  Age    : " << s.age    << "\n";
    cout << "  │  Branch : " << s.branch << "\n";
    cout << "  │  GPA    : " << fixed << setprecision(2) << s.gpa << "\n";
    cout << "  └─────────────────────────────────────────\n";
}

// ─────────────────────────────────────────
//  CRUD operations
// ─────────────────────────────────────────
void addStudent(vector<Student>& students) {
    printHeader("ADD NEW STUDENT");

    Student s;
    cout << "  Enter Student ID   : ";
    while (!(cin >> s.id) || s.id <= 0) {
        cout << "  [!] Invalid ID. Try again: ";
        clearInput();
    }
    if (idExists(students, s.id)) {
        cout << "  [!] A student with ID " << s.id << " already exists.\n";
        clearInput();
        return;
    }
    clearInput();

    cout << "  Enter Name         : ";
    getline(cin, s.name);

    cout << "  Enter Age          : ";
    while (!(cin >> s.age) || s.age <= 0) {
        cout << "  [!] Invalid age. Try again: ";
        clearInput();
    }
    clearInput();

    cout << "  Enter Branch       : ";
    getline(cin, s.branch);

    cout << "  Enter GPA (0-10)   : ";
    while (!(cin >> s.gpa) || s.gpa < 0 || s.gpa > 10) {
        cout << "  [!] Invalid GPA. Try again: ";
        clearInput();
    }
    clearInput();

    students.push_back(s);
    saveStudents(students);
    cout << "\n  ✓ Student added successfully!\n";
}

void displayAllStudents(const vector<Student>& students) {
    printHeader("ALL STUDENT RECORDS");
    if (students.empty()) {
        cout << "  No records found.\n";
        return;
    }
    cout << "  Total records: " << students.size() << "\n\n";
    for (const auto& s : students)
        printStudentRow(s);
}

void searchStudent(const vector<Student>& students) {
    printHeader("SEARCH STUDENT");
    int id;
    cout << "  Enter Student ID to search: ";
    while (!(cin >> id)) { clearInput(); cout << "  Invalid. Try again: "; }
    clearInput();

    int idx = findIndex(students, id);
    if (idx == -1) {
        cout << "  [!] No student found with ID " << id << ".\n";
        return;
    }
    cout << "\n  Record found:\n";
    printStudentRow(students[idx]);
}

void updateStudent(vector<Student>& students) {
    printHeader("UPDATE STUDENT RECORD");
    int id;
    cout << "  Enter Student ID to update: ";
    while (!(cin >> id)) { clearInput(); cout << "  Invalid. Try again: "; }
    clearInput();

    int idx = findIndex(students, id);
    if (idx == -1) {
        cout << "  [!] No student found with ID " << id << ".\n";
        return;
    }

    Student& s = students[idx];
    cout << "\n  Current record:\n";
    printStudentRow(s);

    cout << "\n  Enter new Name     [" << s.name   << "]: ";
    string tmp; getline(cin, tmp);
    if (!tmp.empty()) s.name = tmp;

    cout << "  Enter new Age      [" << s.age    << "]: ";
    int tmpI;
    if (cin >> tmpI && tmpI > 0) s.age = tmpI;
    clearInput();

    cout << "  Enter new Branch   [" << s.branch  << "]: ";
    getline(cin, tmp);
    if (!tmp.empty()) s.branch = tmp;

    cout << "  Enter new GPA      [" << s.gpa     << "]: ";
    float tmpF;
    if (cin >> tmpF && tmpF >= 0 && tmpF <= 10) s.gpa = tmpF;
    clearInput();

    saveStudents(students);
    cout << "\n  ✓ Record updated successfully!\n";
}

void deleteStudent(vector<Student>& students) {
    printHeader("DELETE STUDENT RECORD");
    int id;
    cout << "  Enter Student ID to delete: ";
    while (!(cin >> id)) { clearInput(); cout << "  Invalid. Try again: "; }
    clearInput();

    int idx = findIndex(students, id);
    if (idx == -1) {
        cout << "  [!] No student found with ID " << id << ".\n";
        return;
    }

    cout << "\n  Record to delete:\n";
    printStudentRow(students[idx]);
    cout << "  Confirm delete? (y/n): ";
    char ch; cin >> ch; clearInput();
    if (ch == 'y' || ch == 'Y') {
        students.erase(students.begin() + idx);
        saveStudents(students);
        cout << "\n  ✓ Record deleted successfully!\n";
    } else {
        cout << "  Operation cancelled.\n";
    }
}

// ─────────────────────────────────────────
//  Main menu
// ─────────────────────────────────────────
void showMenu() {
    cout << "\n  ╔══════════════════════════════════════╗\n";
    cout <<   "  ║     STUDENT MANAGEMENT SYSTEM        ║\n";
    cout <<   "  ╠══════════════════════════════════════╣\n";
    cout <<   "  ║  1. Add Student                      ║\n";
    cout <<   "  ║  2. Display All Students             ║\n";
    cout <<   "  ║  3. Search Student                   ║\n";
    cout <<   "  ║  4. Update Student                   ║\n";
    cout <<   "  ║  5. Delete Student                   ║\n";
    cout <<   "  ║  6. Exit                             ║\n";
    cout <<   "  ╚══════════════════════════════════════╝\n";
    cout <<   "  Enter your choice: ";
}

int main() {
    vector<Student> students = loadStudents();
    int choice;

    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            clearInput();
            cout << "  [!] Invalid input. Please enter a number.\n";
            continue;
        }
        clearInput();

        switch (choice) {
            case 1: addStudent(students);          break;
            case 2: displayAllStudents(students);  break;
            case 3: searchStudent(students);       break;
            case 4: updateStudent(students);       break;
            case 5: deleteStudent(students);       break;
            case 6:
                cout << "\n  Goodbye! All records saved.\n\n";
                return 0;
            default:
                cout << "  [!] Invalid choice. Enter 1–6.\n";
        }
    }
}
