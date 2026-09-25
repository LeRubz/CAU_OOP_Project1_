#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    std::string name;          // 15 char
    std::string studentId;     // 10 numbers
    std::string birthYear;     // 4 numbers
    std::string department;
    std::string tel;           // max 12 numbers

public:
    Student();
    Student(const std::string& name, const std::string& studentId,
        const std::string& birthYear, const std::string& department,
        const std::string& tel);

    std::string getName() const;
    std::string getStudentId() const;
    std::string getAdmissionYear() const; // 4 first numbers of studentID
    std::string getBirthYear() const;
    std::string getDepartment() const;
    std::string getTel() const;

    std::string toFileFormat() const;

    void display() const;

    static void displayHeader();
};

#endif