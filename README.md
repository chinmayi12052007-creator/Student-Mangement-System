# Student Management System

A console-based **Student Management System** written in **C++** that efficiently manages student records using **file handling** and **menu-driven operations**.

---

## Features

| Feature | Description |
|---|---|
| ➕ Add Student | Add a new student record with ID, name, age, branch, and GPA |
| 📋 Display All | View all stored student records in a formatted layout |
| 🔍 Search | Find a student by their unique ID |
| ✏️ Update | Modify any field of an existing student record |
| 🗑️ Delete | Remove a student record after confirmation |
| 💾 Persistent Storage | All records are saved to `students.dat` using file I/O |

---

## Project Structure

```
student_management/
├── main.cpp          # Full source code
├── Makefile          # Build automation
├── students.dat      # Auto-generated data file (created on first run)
└── README.md         # Project documentation
```

---

## How to Compile & Run

### Using Makefile (Linux / macOS)
```bash
make          # Compile
make run      # Compile and run
make clean    # Remove binary and data file
```

### Using g++ directly
```bash
g++ -std=c++17 -Wall -o student_management main.cpp
./student_management
```

### On Windows (MinGW)
```bash
g++ -std=c++17 -Wall -o student_management.exe main.cpp
student_management.exe
```

---

## Usage

When you run the program, a menu is displayed:

```
  ╔══════════════════════════════════════╗
  ║     STUDENT MANAGEMENT SYSTEM        ║
  ╠══════════════════════════════════════╣
  ║  1. Add Student                      ║
  ║  2. Display All Students             ║
  ║  3. Search Student                   ║
  ║  4. Update Student                   ║
  ║  5. Delete Student                   ║
  ║  6. Exit                             ║
  ╚══════════════════════════════════════╝
```

- Enter the number corresponding to the operation you want.
- All changes are **automatically saved** to `students.dat`.
- Data **persists between sessions** — no data is lost when you exit.

---

## Student Record Fields

| Field  | Type   | Description              |
|--------|--------|--------------------------|
| ID     | int    | Unique identifier (> 0)  |
| Name   | string | Full name of the student |
| Age    | int    | Age in years             |
| Branch | string | Department / Branch name |
| GPA    | float  | Grade Point Average (0–10) |

---

## File Handling

Student records are stored in a plain-text file `students.dat`. Each student occupies 5 lines:

```
101
John Doe
20
Computer Science
8.75
```

The file is read on startup and updated after every add, update, or delete operation.

---

## Technologies Used

- **Language**: C++ (C++17)
- **Concepts**: File I/O (`fstream`), STL (`vector`, `string`), structs, input validation

---

## Author

> Submitted as part of the C++ console application project.
