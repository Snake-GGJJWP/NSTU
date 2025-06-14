#pragma once
#include "MobileDevice.hpp"

class Ebook : public MobileDevice {
private:
    uint8_t storageGB;  // Storage in GB
    uint32_t bookCapacity;  // Number of books it can store
    bool backlight;

    void validateStorage(uint8_t storage) const;
    void validateBookCapacity(uint32_t capacity) const;

public:
    // Constructor
    Ebook(
        const std::string& model = "Undefined",
        const std::string& color = "Undefined",
        uint16_t year = 2000,
        double price = 0,
        uint8_t storage = 8,
        uint32_t bookCapacity = 100,
        bool backlight = false
    );

    // Getters
    uint8_t getStorage() const { return storageGB; }
    uint32_t getBookCapacity() const { return bookCapacity; }
    bool hasBacklight() const { return backlight; }

    // Setters
    void setStorage(uint8_t storage);
    void setBookCapacity(uint32_t capacity);
    void setBacklight(bool enabled);

    // Virtual functions
    std::string toString() const override;
};