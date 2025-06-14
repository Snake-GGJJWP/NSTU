#pragma once
#include <string>
#include <map>
using namespace std;

enum class Manufacturer {
    APPLE,
    SAMSUNG,
    XIAOMI,
    HTC,
    HUAWEI,
    OPPO,
    VIVO,
    REALME,
    ONEPLUS,
    GOOGLE,
    SONY,
    LG,
    NOKIA,
    MOTOROLA,
    UNDEFINED
};

enum class Color {
    WHITE,
    GRAY,
    BLACK,
    BLUE,
    RED,
    GOLD,
    SILVER,
    GREEN,
    PURPLE,
    PINK,
    YELLOW,
    BRONZE,
    ROSE_GOLD,
    MATTE_BLACK,
    GRADIENT,
    UNDEFINED
};

enum class OS {
    ANDROID,
    IOS,
    HARMONYOS,
    KAIOS,
    UNDEFINED
};

enum class CPU {
    SNAPDRAGON,
    APPLE,
    EXYNOS,
    KIRIN,
    MEDIATEK,
    UNISOC,
    TENSOR,
    BIONIC,
    UNDEFINED
};

string toString(Manufacturer m);
string toString(Color c);
string toString(OS os);
string toString(CPU cpu);

class Specifications {
public:
    Manufacturer manufacturer = Manufacturer::UNDEFINED;
    Color color = Color::UNDEFINED;
    float displaySize = 0.0f;
    int ram = 0;
    int storage = 0;
    CPU cpu = CPU::UNDEFINED;
    OS os = OS::UNDEFINED;

    string getFullSpecs() const;
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