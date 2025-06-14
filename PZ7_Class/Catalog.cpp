#include "Catalog.hpp"
#include <algorithm>

string Catalog::toLowerString(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void Catalog::addSmartphone(string model, double price, string manufacturer,
    string color, string display, string ram,
    string storage, string cpu, string os,
    int releaseYear, int cameraCount,
    string batteryCapacity, bool is5GSupported) {
    try {
        smartphones.emplace_back(model, price, manufacturer, color, display,
            ram, storage, cpu, os, releaseYear,
            cameraCount, batteryCapacity, is5GSupported);
    }
    catch (const invalid_argument& e) {
        cerr << "Error adding smartphone: " << e.what() << endl;
        smartphones.emplace_back(model, Smartphone::getMinPrice(), manufacturer,
            color, display, ram, storage, cpu, os,
            releaseYear, cameraCount, batteryCapacity, is5GSupported);
    }
}

Smartphone Catalog::getSmartphone(string model) const {
    for (const auto& s : smartphones) {
        if (toLowerString(s.getModel()) == toLowerString(model))
            return s;
    }
    return Smartphone();
}

Smartphone Catalog::search(const Smartphone& searchSmartphone) const {
    for (const Smartphone& s : smartphones) {
        if (!searchSmartphone.getModel().empty() &&
            toLowerString(searchSmartphone.getModel()) != toLowerString(s.getModel()))
            continue;

        if (!searchSmartphone.getManufacturer().empty() &&
            toLowerString(searchSmartphone.getManufacturer()) != toLowerString(s.getManufacturer()))
            continue;

        if (!searchSmartphone.getColor().empty() &&
            toLowerString(searchSmartphone.getColor()) != toLowerString(s.getColor()))
            continue;

        if (!searchSmartphone.getDisplay().empty() &&
            toLowerString(searchSmartphone.getDisplay()) != toLowerString(s.getDisplay()))
            continue;

        if (!searchSmartphone.getRAM().empty() &&
            toLowerString(searchSmartphone.getRAM()) != toLowerString(s.getRAM()))
            continue;

        if (!searchSmartphone.getStorage().empty() &&
            toLowerString(searchSmartphone.getStorage()) != toLowerString(s.getStorage()))
            continue;

        if (!searchSmartphone.getCPU().empty() &&
            toLowerString(searchSmartphone.getCPU()) != toLowerString(s.getCPU()))
            continue;

        if (!searchSmartphone.getOS().empty() &&
            toLowerString(searchSmartphone.getOS()) != toLowerString(s.getOS()))
            continue;

        return s;
    }
    return Smartphone();
}