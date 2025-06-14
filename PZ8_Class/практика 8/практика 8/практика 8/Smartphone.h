#pragma once
#include <string>
using namespace std;
enum class Manufacturer {
	APPLE, SAMSUNG, XIAOMI, HTC, UNDEFINED
};
enum class Color {
	WHITE, GRAY, BLACK, BLUE, RED, GOLD, UNDEFINED
};
enum class OS {
	ANDROID, IOS, UNDEFINED
};
enum class CPU {
	SNAPDRAGON, APPLE, UNDEFINED
};
class Smartphone {
private:
	string model;  Manufacturer manufacturer;  Color color;
	float displaySize;  int ram, storage;
	CPU cpu;  OS os;  double price;
public:
	Smartphone();
	Smartphone(string model, double price, Manufacturer manufacturer,
		Color color, float displaySize, int ram,
		int storage, CPU cpu, OS os);
	string getModel() const;
	Manufacturer getManufacturer() const;
	Color getColor() const;
	float getDisplay() const;
	int getRAM() const;
	int getStorage() const;
	CPU getCPU() const;
	OS getOS() const;
	double getPrice() const;
	void setPrice(double price);
};