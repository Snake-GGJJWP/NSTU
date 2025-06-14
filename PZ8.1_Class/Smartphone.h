#pragma once
#include <string>
using namespace std;

enum class Manufacturer { APPLE, SAMSUNG, XIAOMI, HTC, UNDEFINED };
enum class Color { WHITE, GRAY, BLACK, BLUE, RED, GOLD, UNDEFINED };
enum class OS { ANDROID, IOS, UNDEFINED };
enum class CPU { SNAPDRAGON, APPLE, UNDEFINED };

class Specifications {
public:
    Manufacturer manufacturer = Manufacturer::UNDEFINED;
    Color color = Color::UNDEFINED;
    float displaySize = 0.0f;
    int ram = 0;
    int storage = 0;
    CPU cpu = CPU::UNDEFINED;
    OS os = OS::UNDEFINED;
};

class Smartphone {
private:
    string model;
    double price;
    Specifications specs;

public:
    Smartphone();
    Smartphone(string model, double price, const Specifications& specs);

    string getModel() const;
    double getPrice() const;
    const Specifications& getSpecs() const;

    void setPrice(double price);
    void setSpecs(const Specifications& newSpecs);
};