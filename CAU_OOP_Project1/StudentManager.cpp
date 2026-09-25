#include "StudentManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

StudentManager* StudentManager::instance = nullptr;

StudentManager::StudentManager() {
    currentSortStrategy = std::make_unique<SortByName>();
}

StudentManager* StudentManager::getInstance() {
    if (instance == nullptr) {
        instance = new StudentManager();
    }
    return instance;
}

void StudentManager::init(const std::string& filepath) {
    filename = filepath;
    loadFromFile();
}

void StudentManager::loadFromFile() {
    students.clear();
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::ofstream outFile(filename);
        outFile.close();
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string name, id, birthYear, dept, tel;

        if (std::getline(ss, name, '|') &&
            std::getline(ss, id, '|') &&
            std::getline(ss, birthYear, '|') &&
            std::getline(ss, dept, '|') &&
            std::getline(ss, tel, '|')) {
            students.emplace_back(name, id, birthYear, dept, tel);
        }
    }
    inFile.close();
}

void StudentManager::saveToFile() const {
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file for saving: " << filename << std::endl;
        return;
    }

    for (const auto& student : students) {
        outFile << student.toFileFormat() << "\n";
    }
    outFile.close();
}

bool StudentManager::isIdExists(const std::string& studentId) const {
    for (const auto& s : students) {
        if (s.getStudentId() == studentId) {
            return true;
        }
    }
    return false;
}

bool StudentManager::insertStudent(const Student& student) {
    if (isIdExists(student.getStudentId())) {
        std::cout << "Error: Already inserted" << std::endl;
        return false;
    }

    students.push_back(student);

    std::ofstream outFile(filename, std::ios::app);
    if (outFile.is_open()) {
        outFile << student.toFileFormat() << "\n";
        outFile.close();
    }
    return true;
}

void StudentManager::setSortStrategy(std::unique_ptr<SortStrategy> strategy) {
    if (strategy != nullptr) {
        currentSortStrategy = std::move(strategy);
    }
}

void StudentManager::applySort(std::vector<Student>& targetList) const {
    if (currentSortStrategy != nullptr) {
        currentSortStrategy->sort(targetList);
    }
}

std::vector<Student> StudentManager::searchByName(const std::string& keyword) const {
    std::vector<Student> results;
    for (const auto& s : students) {
        if (s.getName().find(keyword) != std::string::npos) {
            results.push_back(s);
        }
    }
    applySort(results);
    return results;
}

std::vector<Student> StudentManager::searchByStudentId(const std::string& studentId) const {
    std::vector<Student> results;
    for (const auto& s : students) {
        if (s.getStudentId() == studentId) {
            results.push_back(s);
        }
    }
    applySort(results);
    return results;
}

std::vector<Student> StudentManager::searchByAdmissionYear(const std::string& year) const {
    std::vector<Student> results;
    for (const auto& s : students) {
        if (s.getAdmissionYear() == year) {
            results.push_back(s);
        }
    }
    applySort(results);
    return results;
}

std::vector<Student> StudentManager::searchByBirthYear(const std::string& year) const {
    std::vector<Student> results;
    for (const auto& s : students) {
        if (s.getBirthYear() == year) {
            results.push_back(s);
        }
    }
    applySort(results);
    return results;
}

std::vector<Student> StudentManager::searchByDepartment(const std::string& dept) const {
    std::vector<Student> results;
    for (const auto& s : students) {
        if (s.getDepartment().find(dept) != std::string::npos) {
            results.push_back(s);
        }
    }
    applySort(results);
    return results;
}

std::vector<Student> StudentManager::getAllStudents() const {
    std::vector<Student> results = students;
    applySort(results);
    return results;
}