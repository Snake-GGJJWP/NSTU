#include "Smartphone.hpp"
#include <iostream>
#include <stdexcept>

const double Smartphone::MIN_PRICE = 50.0;
const double Smartphone::MAX_PRICE = 5000.0;

void Smartphone::validatePrice(double price) const {
    if (price < MIN_PRICE || price > MAX_PRICE) {
        cerr << "Checking the price of the added smartphone:\n";
        cerr << "Warning: Invalid price $" << price
            << ". Price must be between $" << MIN_PRICE
            << " and $" << MAX_PRICE << ".\n";
        throw invalid_argument("Invalid price value");
    }
}

Smartphone::Smartphone() : price(MIN_PRICE), releaseYear(0), cameraCount(0), is5GSupported(false) {}

Smartphone::Smartphone(string model, double price, string manufacturer,
    string color, string display, string ram,
    string storage, string cpu, string os,
    int releaseYear, int cameraCount,
    string batteryCapacity, bool is5GSupported) {
    try {
        validatePrice(price);
        this->price = price;
    }
    catch (const invalid_argument&) {
        this->price = MIN_PRICE;
        cerr << "Setting price to minimum: $" << MIN_PRICE << "\n";
    }

    this->model = model;
    this->manufacturer = manufacturer;
    this->color = color;
    this->display = display;
    this->ram = ram;
    this->storage = storage;
    this->cpu = cpu;
    this->os = os;
    this->releaseYear = releaseYear;
    this->cameraCount = cameraCount;
    this->batteryCapacity = batteryCapacity;
    this->is5GSupported = is5GSupported;
}

void Smartphone::setPrice(double price) {
    try {
        validatePrice(price);
        this->price = price;
    }
    catch (const invalid_argument&) {
        this->price = MIN_PRICE;
        cerr << "Setting price to minimum: $" << MIN_PRICE << "\n";
    }
}

void Smartphone::print() const {
    if (model.empty()) {
        cout << "Smartphone not found" << endl;
        return;
    }

    cout << "\nYou might like this: ";
    cout << manufacturer << " " << model << endl;
    cout << "Price: $" << price;

    if (price < MIN_PRICE || price > MAX_PRICE) {
        cout << " [Warning: Price should be between $"
            << MIN_PRICE << " and $" << MAX_PRICE << "]";
    }
    cout << endl;

    cout << "Color: " << color << endl;
    cout << "Display: " << display << " inches" << endl;
    cout << "OS: " << os << endl;
    cout << ram << "GB RAM, " << storage << "GB storage" << endl;
    cout << "CPU: " << cpu << endl;
    cout << "Release Year: " << releaseYear << endl;
    cout << "Camera Count: " << cameraCount << endl;
    cout << "Battery: " << batteryCapacity << endl;
    cout << "5G Support: " << (is5GSupported ? "Yes" : "No") << endl;
}
