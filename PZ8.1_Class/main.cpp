#include "Smartphone.h"
#include "Catalog.h"
#include <iostream>
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
    Catalog catalog = InitializeCatalog();

    Specifications searchSpecs{ Manufacturer::APPLE, Color::WHITE };
    Smartphone whatBuyerLikes("iphone 12 pro", 0, searchSpecs);

    vector<Smartphone> results = catalog.search(whatBuyerLikes);

    if (!results.empty()) {
        cout << "You might like this:" << endl;
        for (const auto& s : results) {
            const auto& specs = s.getSpecs();
            cout << s.getModel() << endl
                << "Price: " << s.getPrice() << endl
                << "Display: " << specs.displaySize << endl
                << specs.ram << "Gb RAM, " << specs.storage << " GB storage\n\n";
        }
    }
    else {
        cout << "Sorry, we have nothing for you.";
    }

    return 0;
}