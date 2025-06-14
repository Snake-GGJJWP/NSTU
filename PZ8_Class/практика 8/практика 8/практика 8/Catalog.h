#pragma once
#include<string>
#include<vector>
#include"Smartphone.h"
using namespace std;
class Catalog {
private:
    vector<Smartphone> smartphones;
public:
    void addSmartphone(string model, double price, Manufacturer manufacturer,
        Color color, float displaySize, int ram,
        int storage, CPU cpu, OS os);
    Smartphone getSmartphone(string model);
    vector<Smartphone> search(const Smartphone& searchSmartphone);
};