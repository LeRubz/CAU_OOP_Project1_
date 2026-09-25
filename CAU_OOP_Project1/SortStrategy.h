#ifndef SORT_STRATEGY_H
#define SORT_STRATEGY_H

#include <vector>
#include "Student.h"

class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort(std::vector<Student>& students) const = 0;
};

class SortByName : public SortStrategy {
public:
    void sort(std::vector<Student>& students) const override;
};

class SortByStudentId : public SortStrategy {
public:
    void sort(std::vector<Student>& students) const override;
};

class SortByBirthYear : public SortStrategy {
public:
    void sort(std::vector<Student>& students) const override;
};

class SortByDepartment : public SortStrategy {
public:
    void sort(std::vector<Student>& students) const override;
};

#endif