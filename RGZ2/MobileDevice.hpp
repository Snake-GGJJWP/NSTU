#pragma once
#include <string>
#include <stdexcept>

class MobileDevice {
private:
    std::string model;
    std::string color;
    uint16_t year;
    double price;

    void validatePrice(double price) const;
    void validateYear(uint16_t year) const;

public:
    // Parameterized constructor
    MobileDevice(
        const std::string& model = "Undefined",
        const std::string& color = "Undefined",
        uint16_t year = 2000,
        double price = 0);

    virtual ~MobileDevice() = default;

    // Abstract method
    virtual std::string toString() const = 0;

    // Getters
    const std::string& getModel() const { return model; }
    const std::string& getColor() const { return color; }
    uint16_t getYear() const { return year; }
    double getPrice() const { return price; }

    // Setters
    void setModel(const std::string& model) { this->model = model; }
    void setColor(const std::string& color) { this->color = color; }

    void setYear(uint16_t year) {
        validateYear(year);
        this->year = year;
    }

    void setPrice(double price) {
        validatePrice(price);
        this->price = price;
    }
};