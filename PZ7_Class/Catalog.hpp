#pragma once
#include <string>
#include <list>  // „I„x„}„u„~„u„~„€ „ƒ vector „~„p list
#include "Smartphone.hpp"
using namespace std;

class Catalog {
private:
    list<Smartphone> smartphones;  // „I„x„}„u„~„u„~„€ „ƒ vector „~„p list
    static string toLowerString(const string& str);

public:
    void addSmartphone(string model, double price, string manufacturer,
        string color, string display, string ram,
        string storage, string cpu, string os,
        int releaseYear, int cameraCount,
        string batteryCapacity, bool is5GSupported);

    Smartphone getSmartphone(string model) const;
    Smartphone search(const Smartphone& searchSmartphone) const;
};
