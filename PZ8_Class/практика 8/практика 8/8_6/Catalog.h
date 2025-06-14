#pragma once
#include <vector>
#include "Smartphone.h"

class Catalog {
private:
    std::vector<Smartphone> smartphones;

public:
    void addSmartphone(std::string model, double price, const Specifications& specs);
    Smartphone getSmartphone(std::string model);
    std::vector<Smartphone> search(const Smartphone& searchSmartphone);
};