#include <iostream>
#include "StudentCatalog.h"
#include "Student.h"
#include "SubjectMarkList.h"

int main() {
    // СьFдаем ъGенЃE для студентоЃE
    SubjectMarkList marks1;
    marks1.addMark("Math", 90);
    marks1.addMark("Physics", 85);

    SubjectMarkList marks2;
    marks2.addMark("Math", 75);
    marks2.addMark("Physics", 80);

    // СьFдаем студентоЃE
    Student student1("Ivan", "Ivanov", marks1);
    Student student2("Elena", "Sidorova", marks2);

    // Дь@авЃEем студентоЃEЃEЃEтаЃEЃE
    StudentCatalog catalog;
    catalog.addStudent(student1);
    catalog.addStudent(student2);

    // ВывьCим всех студентоЃE
    std::cout << "All students:\n";
    catalog.printAll();

    // ПьGск студентоЃE сдавшиЃEMath ъь 80+ ЃEPhysics ъь 75+
    std::map<std::string, int> criteria = { {"Math", 80}, {"Physics", 75} };
    auto result = catalog.search(criteria);

    std::cout << "\nStudents who passed Math (80+) and Physics (75+):\n";
    for (const auto& student : result) {
        student.print();
    }

    return 0;
}