#include "Smartphone.h"
#include <map>


string toString(Manufacturer m) {
    static const map<Manufacturer, string> names = {
        {Manufacturer::APPLE, "Apple"},
        {Manufacturer::SAMSUNG, "Samsung"},
        {Manufacturer::XIAOMI, "Xiaomi"},
        {Manufacturer::HTC, "HTC"},
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
        {Color::UNDEFINED, "�� ���������"}
    };
    return names.at(c);
}

string toString(OS os) {
    static const map<OS, string> names = {
        {OS::ANDROID, "Android"},
        {OS::IOS, "iOS"},
        {OS::UNDEFINED, "�� ����������"}
    };
    return names.at(os);
}

string toString(CPU cpu) {
    static const map<CPU, string> names = {
        {CPU::SNAPDRAGON, "Snapdragon"},
        {CPU::APPLE, "Apple"},
        {CPU::UNDEFINED, "�� ���������"}
    };
    return names.at(cpu);
}

string Specifications::getFullSpecs() const {
    return "���������: " + to_string(displaySize) + "\n" +
        "���: " + to_string(ram) + " ��\n" +
        "������: " + to_string(storage) + " ��";
}

Smartphone::Smartphone() : model(""), price(0) {}

Smartphone::Smartphone(string model, double price, const Specifications& specs)
    : model(model), price(price), specs(specs) {}

string Smartphone::getModel() const { return model; }
double Smartphone::getPrice() const { return price; }
const Specifications& Smartphone::getSpecs() const { return specs; }

void Smartphone::setPrice(double price) { this->price = price; }
void Smartphone::setSpecs(const Specifications& newSpecs) { specs = newSpecs; }