#include "SortStrategy.h"
#include <algorithm>

void SortByName::sort(std::vector<Student>& students) const {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.getName() < b.getName();
        });
}

void SortByStudentId::sort(std::vector<Student>& students) const {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.getStudentId() < b.getStudentId();
        });
}

void SortByBirthYear::sort(std::vector<Student>& students) const {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.getBirthYear() < b.getBirthYear();
        });
}

void SortByDepartment::sort(std::vector<Student>& students) const {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.getDepartment() < b.getDepartment();
        });
}