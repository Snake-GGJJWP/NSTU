#pragma once
#include "Price.h"
#include <string>
#include <map>

enum class Manufacturer {
    APPLE, SAMSUNG, XIAOMI, HTC, HUAWEI, OPPO, VIVO, REALME,
    ONEPLUS, GOOGLE, SONY, LG, NOKIA, MOTOROLA, UNDEFINED
};

enum class Color {
    WHITE, GRAY, BLACK, BLUE, RED, GOLD, SILVER, GREEN, PURPLE,
    PINK, YELLOW, BRONZE, ROSE_GOLD, MATTE_BLACK, GRADIENT, UNDEFINED
};

enum class OS {
    ANDROID, IOS, HARMONYOS, KAIOS, UNDEFINED
};

enum class CPU {
    SNAPDRAGON, APPLE, EXYNOS, KIRIN, MEDIATEK, UNISOC, TENSOR, BIONIC, UNDEFINED
};

std::string toString(Manufacturer m);
std::string toString(Color c);
std::string toString(OS os);
std::string toString(CPU cpu);

class Specifications {
public:
    Manufacturer manufacturer = Manufacturer::UNDEFINED;
    Color color = Color::UNDEFINED;
    float displaySize = 0.0f;
    int ram = 0;
    int storage = 0;
    CPU cpu = CPU::UNDEFINED;
    OS os = OS::UNDEFINED;

    std::string getFullSpecs() const;
};

class Smartphone {
private:
    std::string model;
    Price price;
    Specifications specs;

public:
    Smartphone();
    Smartphone(std::string model, double price, const Specifications& specs);

    std::string getModel() const;
    double getPrice() const;
    double getPrice(const std::string& currency) const;
    std::string getPriceString(const std::string& currency = "USD") const;
    const Specifications& getSpecs() const;

    void setPrice(double price);
    void setPrice(const Price& price);
    void setSpecs(const Specifications& newSpecs);
};
