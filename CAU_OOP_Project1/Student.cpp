#include "Student.h"
#include <iostream>
#include <iomanip>

Student::Student()
    : name(""), studentId(""), birthYear(""), department(""), tel("") {}

Student::Student(const std::string& name, const std::string& studentId,
    const std::string& birthYear, const std::string& department,
    const std::string& tel)
    : name(name), studentId(studentId), birthYear(birthYear),
    department(department), tel(tel) {}

std::string Student::getName() const {
    return name;
}

std::string Student::getStudentId() const {
    return studentId;
}

std::string Student::getAdmissionYear() const {
    if (studentId.length() >= 4) {
        return studentId.substr(0, 4);
    }
    return "";
}

std::string Student::getBirthYear() const {
    return birthYear;
}

std::string Student::getDepartment() const {
    return department;
}

std::string Student::getTel() const {
    return tel;
}

std::string Student::toFileFormat() const {
    return name + "|" + studentId + "|" + birthYear + "|" + department + "|" + tel;
}

void Student::displayHeader() {
    std::cout << std::left
        << std::setw(18) << "Name"
        << " | " << std::setw(12) << "StudentID"
        << " | " << std::setw(22) << "Dept"
        << " | " << std::setw(10) << "Birth Year"
        << " | " << "Tel"
        << std::endl;
    std::cout << std::string(75, '-') << std::endl;
}

void Student::display() const {
    std::cout << std::left
        << std::setw(18) << name
        << " | " << std::setw(12) << studentId
        << " | " << std::setw(22) << department
        << " | " << std::setw(10) << birthYear
        << " | " << tel
        << std::endl;
}