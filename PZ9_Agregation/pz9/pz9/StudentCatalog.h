#pragma once
#include <vector>
#include "Student.h"

class StudentCatalog {
private:
    std::vector<Student> students;

public:
    void addStudent(const Student& student);
    std::vector<Student> search(const std::map<std::string, int>& criteria) const;
    void printAll() const;
};