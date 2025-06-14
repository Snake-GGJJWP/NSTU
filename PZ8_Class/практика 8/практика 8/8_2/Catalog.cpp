#include "Catalog.h"
#include <algorithm>

void Catalog::addSmartphone(string model, double price, const Specifications& specs) {
    smartphones.emplace_back(model, price, specs);
}

Smartphone Catalog::getSmartphone(string model) {
    transform(model.begin(), model.end(), model.begin(), ::tolower);
    for (const auto& s : smartphones) {
        string currModel = s.getModel();
        transform(currModel.begin(), currModel.end(), currModel.begin(), ::tolower);
        if (currModel == model) return s;
    }
    return Smartphone();
}

vector<Smartphone> Catalog::search(const Smartphone& searchSmartphone) {
    vector<Smartphone> results;
    const auto& searchSpecs = searchSmartphone.getSpecs();

    for (const auto& s : smartphones) {
        const auto& phoneSpecs = s.getSpecs();

        string model = searchSmartphone.getModel();
        transform(model.begin(), model.end(), model.begin(), ::tolower);
        string model2 = s.getModel();
        transform(model2.begin(), model2.end(), model2.begin(), ::tolower);
        if (!model.empty() && model != model2) continue;

        if (searchSpecs.manufacturer != Manufacturer::UNDEFINED &&
            searchSpecs.manufacturer != phoneSpecs.manufacturer) continue;

        if (searchSpecs.color != Color::UNDEFINED &&
            searchSpecs.color != phoneSpecs.color) continue;

        if (searchSpecs.displaySize > 0 &&
            searchSpecs.displaySize != phoneSpecs.displaySize) continue;

        if (searchSpecs.ram > 0 && searchSpecs.ram != phoneSpecs.ram) continue;
        if (searchSpecs.storage > 0 && searchSpecs.storage != phoneSpecs.storage) continue;
        if (searchSpecs.cpu != CPU::UNDEFINED && searchSpecs.cpu != phoneSpecs.cpu) continue;
        if (searchSpecs.os != OS::UNDEFINED && searchSpecs.os != phoneSpecs.os) continue;

        results.push_back(s);
    }
    return results;
}