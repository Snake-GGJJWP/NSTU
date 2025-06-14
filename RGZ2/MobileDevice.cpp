#define _CRT_SECURE_NO_WARNINGS

#include "MobileDevice.hpp"
#include <ctime>

void MobileDevice::validatePrice(double price) const {
    if (price < 0) {
        throw std::invalid_argument("Price cannot be negative");
    }
}

void MobileDevice::validateYear(uint16_t year) const {
    std::time_t t = std::time(nullptr);
    std::tm* const pTInfo = std::localtime(&t);
    int curYear = 1900 + pTInfo->tm_year << '\n';
    
    const uint16_t earliestYear = 1983;
    if (year < earliestYear || year > curYear) {
        throw std::invalid_argument("Invalid year");
    }
}

MobileDevice::MobileDevice(const std::string& model, const std::string& color, uint16_t year, double price)
    : model(model), color(color) {
    validateYear(year);
    validatePrice(price);
    this->year = year;
    this->price = price;
}