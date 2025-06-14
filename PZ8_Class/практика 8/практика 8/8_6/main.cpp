#include "Smartphone.h"
#include "Catalog.h"
#include <iostream>
#include <locale.h>

Catalog InitializeCatalog() {
    Catalog catalog;

    Specifications specs1{ Manufacturer::APPLE, Color::WHITE, 6.1f, 4, 128, CPU::APPLE, OS::IOS };
    catalog.addSmartphone("iPhone 13", 799.0, specs1);

    Specifications specs2{ Manufacturer::SAMSUNG, Color::BLACK, 6.5f, 8, 256, CPU::EXYNOS, OS::ANDROID };
    catalog.addSmartphone("Galaxy S21", 699.0, specs2);

    Specifications specs3{ Manufacturer::XIAOMI, Color::BLUE, 6.67f, 6, 128, CPU::SNAPDRAGON, OS::ANDROID };
    catalog.addSmartphone("Redmi Note 10 Pro", 299.0, specs3);

    return catalog;
}

int main() {
    setlocale(LC_ALL, "rus");
    Catalog catalog = InitializeCatalog();

    Specifications searchSpecs{ Manufacturer::APPLE, Color::WHITE };
    Smartphone whatBuyerLikes("iPhone 13", 0, searchSpecs);

    std::vector<Smartphone> results = catalog.search(whatBuyerLikes);

    if (!results.empty()) {
        std::cout << "You might like:" << std::endl;
        for (const auto& s : results) {
            std::cout << "Model: " << s.getModel() << std::endl
                << "Price USD: " << s.getPriceString("USD") << std::endl
                << "Price RUB: " << s.getPriceString("RUB") << std::endl
                << "Price EUR: " << s.getPriceString("EUR") << std::endl
                << s.getSpecs().getFullSpecs() << std::endl << std::endl;
        }
    }
    else {
        std::cout << "Sorry, no products were found";
    }

    return 0;
}