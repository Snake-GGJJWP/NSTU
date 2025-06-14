#include "SubjectMarkList.h"
#include <iostream>

void SubjectMarkList::addMark(const std::string& subject, int mark) {
    subjects[subject] = mark;
}

bool SubjectMarkList::satisfies(const std::map<std::string, int>& criteria) const {
    for (const auto& pair : criteria) {
        const std::string& subject = pair.first;
        int minMark = pair.second;

        auto it = subjects.find(subject);
        if (it == subjects.end() || it->second < minMark) {
            return false;
        }
    }
    return true;
}

void SubjectMarkList::print() const {
    for (const auto& pair : subjects) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
}