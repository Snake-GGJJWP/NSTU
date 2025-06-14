#include "Student.h"
#include <iostream>

Student::Student(std::string firstName, std::string lastName, const SubjectMarkList& marks)
    : firstName(firstName), lastName(lastName), marks(marks) {}

std::string Student::getFullName() const {
    return firstName + " " + lastName;
}

const SubjectMarkList& Student::getMarks() const {
    return marks;
}

void Student::print() const {
    std::cout << getFullName() << std::endl;
    marks.print();
}