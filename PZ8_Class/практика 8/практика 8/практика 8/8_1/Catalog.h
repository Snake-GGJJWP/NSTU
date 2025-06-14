#pragma once
#include <vector>
#include "Smartphone.h"
using namespace std;

class Catalog {
private:
    vector<Smartphone> smartphones;

public:
    void addSmartphone(string model, double price, const Specifications& specs);
    Smartphone getSmartphone(string model);
    vector<Smartphone> search(const Smartphone& searchSmartphone);
};