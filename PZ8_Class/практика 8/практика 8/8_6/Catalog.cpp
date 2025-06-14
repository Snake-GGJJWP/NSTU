#include "Catalog.h"
#include <algorithm>

void Catalog::addSmartphone(std::string model, double price, const Specifications& specs) {
    smartphones.emplace_back(model, price, specs);
}

Smartphone Catalog::getSmartphone(std::string model) {
    std::transform(model.begin(), model.end(), model.begin(), ::tolower);
    for (const auto& s : smartphones) {
        std::string currModel = s.getModel();
        std::transform(currModel.begin(), currModel.end(), currModel.begin(), ::tolower);
        if (currModel == model) return s;
    }
    return Smartphone();
}

std::vector<Smartphone> Catalog::search(const Smartphone& searchSmartphone) {
    std::vector<Smartphone> results;
    const auto& searchSpecs = searchSmartphone.getSpecs();

    for (const auto& s : smartphones) {
        const auto& phoneSpecs = s.getSpecs();

        std::string model = searchSmartphone.getModel();
        std::transform(model.begin(), model.end(), model.begin(), ::tolower);
        std::string model2 = s.getModel();
        std::transform(model2.begin(), model2.end(), model2.begin(), ::tolower);
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
