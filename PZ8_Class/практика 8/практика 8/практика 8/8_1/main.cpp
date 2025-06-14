#include "Smartphone.h"
#include "Catalog.h"
#include <iostream>
#include <locale.h>
using namespace std;

Catalog InitializeCatalog() {
    Catalog catalog;

    Specifications specs1{ Manufacturer::APPLE, Color::WHITE, 6.0f, 3, 64, CPU::APPLE, OS::IOS };
    catalog.addSmartphone("iPhone 12 Pro", 100, specs1);

    Specifications specs2{ Manufacturer::APPLE, Color::WHITE, 6.0f, 3, 128, CPU::APPLE, OS::IOS };
    catalog.addSmartphone("iPhone 12 Pro", 102, specs2);

    Specifications specs3{ Manufacturer::APPLE, Color::BLUE, 6.0f, 3, 64, CPU::APPLE, OS::IOS };
    catalog.addSmartphone("iPhone 12 Pro", 98, specs3);

    return catalog;
}

int main() {
    setlocale(LC_ALL, "rus");
    Catalog catalog = InitializeCatalog();

    Specifications searchSpecs{ Manufacturer::APPLE, Color::WHITE };
    Smartphone whatBuyerLikes("iphone 12 pro", 0, searchSpecs);

    vector<Smartphone> results = catalog.search(whatBuyerLikes);

    if (!results.empty()) {
        cout << "Вам могут понравиться:" << endl;
        for (const auto& s : results) {
            cout << "Модель: " << s.getModel() << endl
                << "Цена: " << s.getPrice() << " $" << endl
                << s.getSpecs().getFullSpecs() << endl << endl;
        }
    }
    else {
        cout << "Извините, нам нечего вам предложить.";
    }

    return 0;
}