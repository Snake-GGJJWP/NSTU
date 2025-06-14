#include "Smartphone.h"
#include <map>
#include <sstream>
#include <iomanip>

string toString(Manufacturer m) {
    static const map<Manufacturer, string> names = {
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
        {Manufacturer::UNDEFINED, "�� ���������"}
    };
    return names.at(m);
}

string toString(Color c) {
    static const map<Color, string> names = {
        {Color::WHITE, "�����"},
        {Color::GRAY, "�����"},
        {Color::BLACK, "׸����"},
        {Color::BLUE, "�����"},
        {Color::RED, "�������"},
        {Color::GOLD, "�������"},
        {Color::SILVER, "����������"},
        {Color::GREEN, "������"},
        {Color::PURPLE, "����������"},
        {Color::PINK, "�������"},
        {Color::YELLOW, "Ƹ����"},
        {Color::BRONZE, "���������"},
        {Color::ROSE_GOLD, "������� ������"},
        {Color::MATTE_BLACK, "������� ������"},
        {Color::GRADIENT, "��������"},
        {Color::UNDEFINED, "�� ���������"}
    };
    return names.at(c);
}

string toString(OS os) {
    static const map<OS, string> names = {
        {OS::ANDROID, "Android"},
        {OS::IOS, "iOS"},
        {OS::HARMONYOS, "HarmonyOS"},
        {OS::KAIOS, "KaiOS"},
        {OS::UNDEFINED, "�� ����������"}
    };
    return names.at(os);
}

string toString(CPU cpu) {
    static const map<CPU, string> names = {
        {CPU::SNAPDRAGON, "Snapdragon"},
        {CPU::APPLE, "Apple"},
        {CPU::EXYNOS, "Exynos"},
        {CPU::KIRIN, "Kirin"},
        {CPU::MEDIATEK, "MediaTek"},
        {CPU::UNISOC, "Unisoc"},
        {CPU::TENSOR, "Tensor"},
        {CPU::BIONIC, "Bionic"},
        {CPU::UNDEFINED, "�� ���������"}
    };
    return names.at(cpu);
}

string Specifications::getFullSpecs() const {
    return "�������������: " + toString(manufacturer) + "\n" +
        "����: " + toString(color) + "\n" +
        "���������: " + to_string(displaySize) + "\"\n" +
        "���: " + to_string(ram) + " ��\n" +
        "������: " + to_string(storage) + " ��\n" +
        "���������: " + toString(cpu) + "\n" +
        "��: " + toString(os);
}

Smartphone::Smartphone() : model(""), price(0) {}

Smartphone::Smartphone(string model, double price, const Specifications& specs)
    : model(model), price(price), specs(specs) {}

string Smartphone::getModel() const { return model; }
double Smartphone::getPrice() const { return price; }
const Specifications& Smartphone::getSpecs() const { return specs; }

void Smartphone::setPrice(double price) { this->price = price; }
void Smartphone::setSpecs(const Specifications& newSpecs) { specs = newSpecs; }