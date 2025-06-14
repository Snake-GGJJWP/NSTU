#include "Smartphone.hpp"
#include <sstream>
#include <algorithm>

void Smartphone::validateRAM(uint8_t ram) const {
    if (ram < 1 || ram > 32) {
        throw std::invalid_argument("RAM must be between 1-32 GB");
    }
}

void Smartphone::validateStorage(uint16_t storage) const {
    if (storage < 8 || storage > 1024) {
        throw std::invalid_argument("Storage must be between 8-1024 GB");
    }
}

Smartphone::Smartphone(
    const std::string& model,
    const std::string& color,
    uint16_t year,
    double price,
    uint8_t ram,
    uint16_t storage)
    : MobileDevice(model, color, year, price) 
{
    setRAM(ram);
    setStorage(storage);
}

void Smartphone::setRAM(uint8_t ram) {
    validateRAM(ram);
    ramGB = ram;
}

void Smartphone::setStorage(uint16_t storage) {
    validateStorage(storage);
    storageGB = storage;
}

void Smartphone::addApp(const std::string& appName) {
    installedApps.push_back(appName);
}

bool Smartphone::removeApp(const std::string& appName) {
    auto it = std::remove(installedApps.begin(), installedApps.end(), appName);
    if (it != installedApps.end()) {
        installedApps.erase(it, installedApps.end());
        return true;
    }
    return false;
}

std::string Smartphone::toString() const{
    std::ostringstream oss;
    oss << "Smartphone [Model: " << getModel()
        << ", Color: " << getColor()
        << ", Year: " << getYear()
        << ", Price: $" << getPrice()
        << ", RAM: " << (int)ramGB << "GB"
        << ", Storage: " << storageGB << "GB"
        << ", Apps: " << installedApps.size() << "]";
    return oss.str();
}