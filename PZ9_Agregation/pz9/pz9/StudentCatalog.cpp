#include "StudentCatalog.h"
#include <iostream>

void StudentCatalog::addStudent(const Student& student) {
    students.push_back(student);
}

std::vector<Student> StudentCatalog::search(const std::map<std::string, int>& criteria) const {
    std::vector<Student> result;
    for (const auto& student : students) {
        if (student.getMarks().satisfies(criteria)) {
            result.push_back(student);
        }
    }
    return result;
}

void StudentCatalog::printAll() const {
    for (const auto& student : students) {
        student.print();
        
    }
}