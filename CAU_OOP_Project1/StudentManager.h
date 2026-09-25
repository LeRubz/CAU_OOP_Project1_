#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "Student.h"
#include "SortStrategy.h"

class StudentManager {
private:
    static StudentManager* instance;
    std::string filename;
    std::vector<Student> students;
    std::unique_ptr<SortStrategy> currentSortStrategy;

    StudentManager();
    ~StudentManager() = default;

    StudentManager(const StudentManager&) = delete;
    StudentManager& operator=(const StudentManager&) = delete;

public:
    static StudentManager* getInstance();

    void init(const std::string& filepath);
    void loadFromFile();
    void saveToFile() const;

    bool insertStudent(const Student& student);
    bool isIdExists(const std::string& studentId) const;

    void setSortStrategy(std::unique_ptr<SortStrategy> strategy);
    void applySort(std::vector<Student>& targetList) const;

    std::vector<Student> searchByName(const std::string& keyword) const;
    std::vector<Student> searchByStudentId(const std::string& studentId) const;
    std::vector<Student> searchByAdmissionYear(const std::string& year) const;
    std::vector<Student> searchByBirthYear(const std::string& year) const;
    std::vector<Student> searchByDepartment(const std::string& dept) const;
    std::vector<Student> getAllStudents() const;
};

#endif