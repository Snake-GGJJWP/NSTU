#pragma once
#include <string>
#include "SubjectMarkList.h"

class Student {
private:
    std::string firstName;
    std::string lastName;
    SubjectMarkList marks;

public:
    Student(std::string firstName, std::string lastName, const SubjectMarkList& marks);
    std::string getFullName() const;
    const SubjectMarkList& getMarks() const;
    void print() const;
};