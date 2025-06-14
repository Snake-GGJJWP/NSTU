#include "Smartphone.hpp"
#include "Ebook.hpp"
#include <iostream>
#include <list>
#include <memory>

int main() {
	try {
		std::list<std::unique_ptr<MobileDevice>> list;
		list.push_back(std::unique_ptr<Smartphone>(new Smartphone("Apple")));
		list.push_back(std::unique_ptr<Ebook>(new Ebook("Samsung")));
		list.push_back(std::unique_ptr<Smartphone>(new Smartphone("NSU")));
		list.push_back(std::unique_ptr<Ebook>(new Ebook("NSTU")));

		for (auto& device : list) {
			static int i = 1;
			std::cout << "Device " << i << ":" << device->toString() << std::endl;
			i++;
		}
	}
	catch (std::exception& e) {
		std::cerr << "[WARNING]:" << e.what() << std::endl;
	}
}