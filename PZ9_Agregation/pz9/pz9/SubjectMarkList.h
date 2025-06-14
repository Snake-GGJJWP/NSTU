#pragma once
#include <map>
#include <string>

class SubjectMarkList {
private:
    std::map<std::string, int> subjects; // �E��E�E? �G��E

public:
    void addMark(const std::string& subject, int mark);
    bool satisfies(const std::map<std::string, int>& criteria) const;
    void print() const;
};