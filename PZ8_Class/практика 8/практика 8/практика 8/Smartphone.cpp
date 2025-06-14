#include "Smartphone.h"

Smartphone::Smartphone() {
	this->model = "";  this->price = 0;
	this->manufacturer = Manufacturer::UNDEFINED;
	this->color = Color::UNDEFINED;
	this->displaySize = 0;  this->ram = 0;
	this->storage = 0;
	this->cpu = CPU::UNDEFINED;  this->os = OS::UNDEFINED;
}

Smartphone::Smartphone(string model, double price, Manufacturer manufacturer,
	Color color, float displaySize, int ram,
	int storage, CPU cpu, OS os) {
	this->model = model;  this->price = price;
	this->manufacturer = manufacturer;
	this->color = color;
	this->displaySize = displaySize;  this->ram = ram;
	this->storage = storage;
	this->cpu = cpu;  this->os = os;
}

string Smartphone::getModel() const {
	return model;
}

Manufacturer Smartphone::getManufacturer() const {
	return manufacturer;
}

Color Smartphone::getColor() const {
	return color;
}

float Smartphone::getDisplay() const {
	return displaySize;
}

int Smartphone::getRAM() const {
	return ram;
}

int Smartphone::getStorage() const {
	return storage;
}

CPU Smartphone::getCPU() const {
	return cpu;
}

OS Smartphone::getOS() const {
	return os;
}

double Smartphone::getPrice() const {
	return price;
}

void Smartphone::setPrice(double price) {
	this->price = price;
}