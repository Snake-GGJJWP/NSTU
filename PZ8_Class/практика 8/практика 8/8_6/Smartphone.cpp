#include "Smartphone.h"
#include <map>
#include <sstream>
#include <iomanip>

std::string toString(Manufacturer m) {
    static const std::map<Manufacturer, std::string> names = {
        {Manufacturer::APPLE, "Apple"},
        {Manufacturer::SAMSUNG, "Samsung"},
        {Manufacturer::XIAOMI, "Xiaomi"},
        {Manufacturer::HTC, "HTC"},
        {Manufacturer::HUAWEI, "Huawei"},
        {Manufacturer::OPPO, "Oppo"},
        {Manufacturer::VIVO, "Vivo"},
        {Manufacturer::REALME, "Realme"},
        {Manufacturer::ONEPLUS, "OnePlus"},
        {Manufacturer::GOOGLE, "Google"},
        {Manufacturer::SONY, "Sony"},
        {Manufacturer::LG, "LG"},
        {Manufacturer::NOKIA, "Nokia"},
        {Manufacturer::MOTOROLA, "Motorola"},
        {Manufacturer::UNDEFINED, "Undefined"}
    };
    return names.at(m);
}

std::string toString(Color c) {
    static const std::map<Color, std::string> names = {
        {Color::WHITE, "White"},
        {Color::GRAY, "Gray"},
        {Color::BLACK, "Black"},
        {Color::BLUE, "Blue"},
        {Color::RED, "Red"},
        {Color::GOLD, "Gold"},
        {Color::SILVER, "Silver"},
        {Color::GREEN, "Green"},
        {Color::PURPLE, "Purple"},
        {Color::PINK, "Pink"},
        {Color::YELLOW, "Yellow"},
        {Color::BRONZE, "Bronze"},
        {Color::ROSE_GOLD, "Rose gold"},
        {Color::MATTE_BLACK, "Matte black"},
        {Color::GRADIENT, "Gradient"},
        {Color::UNDEFINED, "Undefined"}
    };
    return names.at(c);
}

std::string toString(OS os) {
    static const std::map<OS, std::string> names = {
        {OS::ANDROID, "Android"},
        {OS::IOS, "iOS"},
        {OS::HARMONYOS, "HarmonyOS"},
        {OS::KAIOS, "KaiOS"},
        {OS::UNDEFINED, "Undefined"}
    };
    return names.at(os);
}

std::string toString(CPU cpu) {
    static const std::map<CPU, std::string> names = {
        {CPU::SNAPDRAGON, "Snapdragon"},
        {CPU::APPLE, "Apple"},
        {CPU::EXYNOS, "Exynos"},
        {CPU::KIRIN, "Kirin"},
        {CPU::MEDIATEK, "MediaTek"},
        {CPU::UNISOC, "Unisoc"},
        {CPU::TENSOR, "Tensor"},
        {CPU::BIONIC, "Bionic"},
        {CPU::UNDEFINED, "Undefined"}
    };
    return names.at(cpu);
}

std::string Specifications::getFullSpecs() const {
    return "Manufacturer: " + toString(manufacturer) + "\n" +
        "Color: " + toString(color) + "\n" +
        "Screen: " + std::to_string(displaySize) + "\n" +
        "RAM: " + std::to_string(ram) + " GB\n" +
        "Storage: " + std::to_string(storage) + " GB\n" +
        "CPU: " + toString(cpu) + "\n" +
        "OS: " + toString(os);
}

Smartphone::Smartphone() : model(""), price(0) {}

Smartphone::Smartphone(std::string model, double price, const Specifications& specs)
    : model(model), price(price), specs(specs) {}

std::string Smartphone::getModel() const { return model; }
double Smartphone::getPrice() const { return price.getAmount(); }
double Smartphone::getPrice(const std::string& currency) const { return price.getAmount(currency); }
std::string Smartphone::getPriceString(const std::string& currency) const { return price.toString(currency); }
const Specifications& Smartphone::getSpecs() const { return specs; }

void Smartphone::setPrice(double price) { this->price.setAmount(price); }
void Smartphone::setPrice(const Price& price) { this->price = price; }
void Smartphone::setSpecs(const Specifications& newSpecs) { specs = newSpecs; }
