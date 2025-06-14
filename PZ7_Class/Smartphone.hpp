#pragma once
#include <string>
#include <iostream>
using namespace std;

class Smartphone {
private:
    string model, manufacturer, color, display, ram, storage, cpu, os;
    double price;
    int releaseYear;
    int cameraCount;
    string batteryCapacity;
    bool is5GSupported;

    static const double MIN_PRICE;
    static const double MAX_PRICE;

    void validatePrice(double price) const;

public:
    Smartphone();
    Smartphone(string model, double price, string manufacturer,
        string color, string display, string ram,
        string storage, string cpu, string os,
        int releaseYear, int cameraCount,
        string batteryCapacity, bool is5GSupported);

    // ÑCÑuÑÑÑÑÑuÑÇÑç
    string getModel() const { return model; }
    string getManufacturer() const { return manufacturer; }
    string getColor() const { return color; }
    string getDisplay() const { return display; }
    string getRAM() const { return ram; }
    string getStorage() const { return storage; }
    string getCPU() const { return cpu; }
    string getOS() const { return os; }
    double getPrice() const { return price; }
    int getReleaseYear() const { return releaseYear; }
    int getCameraCount() const { return cameraCount; }
    string getBatteryCapacity() const { return batteryCapacity; }
    bool getIs5GSupported() const { return is5GSupported; }

    // ÑRÑuÑÑÑÑÑuÑÇÑç
    void setPrice(double price);
    void setReleaseYear(int year) { releaseYear = year; }
    void setCameraCount(int count) { cameraCount = count; }
    void setBatteryCapacity(string capacity) { batteryCapacity = capacity; }
    void setIs5GSupported(bool supported) { is5GSupported = supported; }

    static double getMinPrice() { return MIN_PRICE; }
    static double getMaxPrice() { return MAX_PRICE; }

    void print() const;
};
