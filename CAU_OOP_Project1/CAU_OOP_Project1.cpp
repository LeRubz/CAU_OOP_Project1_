#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Student.h"
#include "StudentManager.h"
#include "SortStrategy.h"

void printResults(const std::vector<Student>& list) {
    if (list.empty()) {
        std::cout << "No student found." << std::endl;
        return;
    }
    Student::displayHeader();
    for (const auto& s : list) {
        s.display();
    }
}

void clearInputBuffer() {
    std::cin.clear();
    while (std::cin.get() != '\n') {
    }
}

// 1. Menu Insertion
void handleInsertion(StudentManager* manager) {
    std::string name, studentId, birthYear, dept, tel;

    std::cout << "Name ? ";
    std::getline(std::cin, name);

    std::cout << "Student ID (10 digits)? ";
    std::getline(std::cin, studentId);

    std::cout << "Birth Year (4 digits)? ";
    std::getline(std::cin, birthYear);

    std::cout << "Department ? ";
    std::getline(std::cin, dept);

    std::cout << "Tel? ";
    std::getline(std::cin, tel);

    if (name.empty() || studentId.empty()) {
        std::cout << "Error: Name and Student ID must not be blank." << std::endl;
        return;
    }

    if (name.length() > 15) {
        std::cout << "Error: Name must be up to 15 characters." << std::endl;
        return;
    }

    if (studentId.length() != 10) {
        std::cout << "Error: Student ID must be exactly 10 digits." << std::endl;
        return;
    }

    if (birthYear.length() != 4) {
        std::cout << "Error: Birth Year must be exactly 4 digits." << std::endl;
        return;
    }

    if (tel.length() > 12) {
        std::cout << "Error: Tel must be up to 12 digits." << std::endl;
        return;
    }

    Student newStudent(name, studentId, birthYear, dept, tel);
    manager->insertStudent(newStudent);
}

void handleSearch(StudentManager* manager) {
    std::cout << "\n--------------------\nSearch\n";
    std::cout << "1. Search by name\n";
    std::cout << "2. Search by student ID (10 digits)\n";
    std::cout << "3. Search by admission year (4 digits)\n";
    std::cout << "4. Search by birth year (4 digits)\n";
    std::cout << "5. Search by department name\n";
    std::cout << "6. List All\n";
    std::cout << "> ";

    int choice = 0;
    if (!(std::cin >> choice)) {
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    std::string keyword;
    std::vector<Student> results;

    switch (choice) {
    case 1:
        std::cout << "Name keyword? ";
        std::getline(std::cin, keyword);
        results = manager->searchByName(keyword);
        break;
    case 2:
        std::cout << "Student ID? ";
        std::getline(std::cin, keyword);
        results = manager->searchByStudentId(keyword);
        break;
    case 3:
        std::cout << "Admission year (4 digits)? ";
        std::getline(std::cin, keyword);
        results = manager->searchByAdmissionYear(keyword);
        break;
    case 4:
        std::cout << "Birth year (4 digits)? ";
        std::getline(std::cin, keyword);
        results = manager->searchByBirthYear(keyword);
        break;
    case 5:
        std::cout << "Department name keyword? ";
        std::getline(std::cin, keyword);
        results = manager->searchByDepartment(keyword);
        break;
    case 6:
        results = manager->getAllStudents();
        break;
    default:
        std::cout << "Invalid search choice." << std::endl;
        return;
    }

    printResults(results);
}

void handleSortingOption(StudentManager* manager) {
    std::cout << "\n--------------------\nSorting Option\n";
    std::cout << "1. Sort by Name\n";
    std::cout << "2. Sort by Student ID\n";
    std::cout << "3. Sort by Birth Year\n";
    std::cout << "4. Sort by Department name\n";
    std::cout << "> ";

    int choice = 0;
    if (!(std::cin >> choice)) {
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    switch (choice) {
    case 1:
        manager->setSortStrategy(std::make_unique<SortByName>());
        break;
    case 2:
        manager->setSortStrategy(std::make_unique<SortByStudentId>());
        break;
    case 3:
        manager->setSortStrategy(std::make_unique<SortByBirthYear>());
        break;
    case 4:
        manager->setSortStrategy(std::make_unique<SortByDepartment>());
        break;
    default:
        std::cout << "Invalid sorting choice." << std::endl;
        break;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    StudentManager* manager = StudentManager::getInstance();
    manager->init(filename);

    int choice = 0;
    while (true) {
        std::cout << "\n1. Insertion\n";
        std::cout << "2. Search\n";
        std::cout << "3. Sorting Option\n";
        std::cout << "4. Exit\n";
        std::cout << "> ";

        if (!(std::cin >> choice)) {
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (choice == 1) {
            handleInsertion(manager);
        }
        else if (choice == 2) {
            handleSearch(manager);
        }
        else if (choice == 3) {
            handleSortingOption(manager);
        }
        else if (choice == 4) {
            manager->saveToFile();
            break;
        }
        else {
            std::cout << "Invalid menu choice. Please select 1-4." << std::endl;
        }
    }

    return 0;
}