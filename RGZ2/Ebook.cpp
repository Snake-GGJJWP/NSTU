#include "Ebook.hpp"
#include <sstream>

void Ebook::validateStorage(uint8_t storage) const {
    if (storage < 1 || storage > 32) {
        throw std::invalid_argument("Storage must be between 1-32 GB");
    }
}

void Ebook::validateBookCapacity(uint32_t capacity) const {
    if (capacity < 100 || capacity > 100000) {
        throw std::invalid_argument("Book capacity must be between 100-100000");
    }
}

Ebook::Ebook(
    const std::string& model,
    const std::string& color,
    uint16_t year,
    double price,
    uint8_t storage,
    uint32_t bookCapacity,
    bool hasBacklight)
    : MobileDevice(model, color, year, price) {
    setStorage(storage);
    setBookCapacity(bookCapacity);
    setBacklight(hasBacklight);
}

void Ebook::setStorage(uint8_t storage) {
    validateStorage(storage);
    storageGB = storage;
}

void Ebook::setBookCapacity(uint32_t capacity) {
    validateBookCapacity(capacity);
    bookCapacity = capacity;
}

void Ebook::setBacklight(bool enabled) {
    backlight = enabled;
}

std::string Ebook::toString() const {
    std::ostringstream oss;
    oss << "Ebook [Model: " << getModel()
        << ", Color: " << getColor()
        << ", Year: " << getYear()
        << ", Price: $" << getPrice()
        << ", Storage: " << (int)storageGB << "GB"
        << ", Capacity: " << bookCapacity << " books"
        << ", Backlight: " << (backlight ? "Yes" : "No") << "]";
    return oss.str();
}